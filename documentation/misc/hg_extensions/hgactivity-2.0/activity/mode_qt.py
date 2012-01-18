#!/usr/bin/env python
# -*- coding: utf-8
# vim: set fileencoding=utf-8

# Copyright 2011 Thomas Capricelli <orzel@freehackers.org>
# mercurial extension released under the GNU General Public Licence (GPLv2)

# qt
try:
    from PyQt4 import QtGui, QtCore
except:
    raise UiException('you need PyQt to use --mode=gui')

# matplotlib
try:
    import matplotlib
    from matplotlib.figure import Figure
except:
    raise UiException('you need matplotlib in your python path in order to use the hg activity extension.')

# matplotlib _with_ qt support
try:
    from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
    from matplotlib.backends.backend_qt4agg import NavigationToolbar2QTAgg as NavigationToolbar
except:
    raise UiException('Matplotlib does not have the Qt backend, which is needed by hg activity with --mode=gui, please re-compile/re-install it.')

from datetime import datetime, timedelta, time
from draw import draw_graph
from mainwindow import Ui_MainWindow
from data import collect_data
from configurationwidget import Ui_ConfigurationWidget
from . import split_list

class MainWindow(QtGui.QMainWindow):
    def __init__(self, repo, options, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.repo = repo
        self.options = options

        self.createConfigurationWidget()
        self.createLayout()

        # initialize stuff
        self.splitChanged(split_list.index(self.options.split)) # fetch + redraw

    def createConfigurationWidget(self):
        self.configurationwidget = QtGui.QGroupBox()
        self.cwui = Ui_ConfigurationWidget()
        self.cwui.setupUi(self.configurationwidget)

        # set initial values
        self.cwui.splitComboBox.setCurrentIndex(split_list.index(self.options.split))
        if self.options.filename:
            self.cwui.filenameLineEdit.setText(self.options.filename)
        if self.options.imagetitle:
            self.cwui.imageTitleLineEdit.setText(self.options.imagetitle)
        if self.options.skipmerges:
            self.cwui.skipMergesCheckBox.setCheckState(QtCore.Qt.Checked)
        if self.options.showtags:
            self.cwui.showTagsCheckBox.setCheckState(QtCore.Qt.Checked)
        if self.options.uselines:
            self.cwui.uselinesCheckBox.setCheckState(QtCore.Qt.Checked)
        self.cwui.maxcaptionSpinBox.setValue(self.options.maxcaptions)

        # overall min/max
        self.cwui.startDateEdit.setMinimumDate(self.options.repo_datemin)
        self.cwui.endDateEdit.setMaximumDate(self.options.repo_datemax)
        # initial value
        if self.options.datemin == None:
            self.cwui.startDateEdit.setDate(self.options.repo_datemin)
        else:
            self.cwui.startDateEdit.setDate(self.options.datemin)
        if self.options.datemax == None:
            self.cwui.endDateEdit.setDate(self.options.repo_datemax)
        else:
            self.cwui.endDateEdit.setDate(self.options.datemax)
        if self.options.datemin != None or self.options.datemax != None:
            self.timerangeUpdate(4) # 4 = custom
            self.cwui.timerangeComboBox.setCurrentIndex(4)
        else:
            self.timerangeUpdate(0) # 0 = whole range
            self.cwui.timerangeComboBox.setCurrentIndex(0)

        #
        # connect them all
        #
        self.connect(self.cwui.splitComboBox, QtCore.SIGNAL('currentIndexChanged(int)'), self.splitChanged)
        self.connect(self.cwui.timerangeComboBox, QtCore.SIGNAL('currentIndexChanged(int)'), self.timerangeChanged)
        self.connect(self.cwui.filenameLineEdit, QtCore.SIGNAL('textChanged(const QString)'), self.filenameChanged)
        self.connect(self.cwui.imageTitleLineEdit, QtCore.SIGNAL('textChanged(const QString)'), self.imageTitleChanged)
        self.connect(self.cwui.skipMergesCheckBox, QtCore.SIGNAL('stateChanged(int)'), self.skipMergesChanged)
        self.connect(self.cwui.showTagsCheckBox, QtCore.SIGNAL('stateChanged(int)'), self.showTagsChanged)
        self.connect(self.cwui.uselinesCheckBox, QtCore.SIGNAL('stateChanged(int)'), self.uselinesChanged)
        self.connect(self.cwui.maxcaptionSpinBox, QtCore.SIGNAL('valueChanged(int)'), self.maxcaptionChanged)

        self.connect(self.cwui.startDateEdit, QtCore.SIGNAL('dateChanged(const QDate&)'), self.timerangeChanged)
        self.connect(self.cwui.endDateEdit, QtCore.SIGNAL('dateChanged(const QDate&)'), self.timerangeChanged)

        #
        # remaining mainwindow stuff
        #
        self.connect(self.ui.action_About, QtCore.SIGNAL('triggered()'), self.about)
        self.connect(self.ui.action_Quit, QtCore.SIGNAL('triggered()'), QtGui.qApp.quit)


    def createLayout(self):
        # layout
        vbox = QtGui.QVBoxLayout()
        hbox = QtGui.QHBoxLayout()

        self.fig = Figure()
        self.fig.add_subplot(111)
        self.canvas = FigureCanvas(self.fig)
        self.canvas.setParent(self.ui.centralWidget)
        self.canvas.setMinimumSize(50,50)
        hbox.addWidget(self.canvas, 1.)
        hbox.addWidget(self.configurationwidget)

        vbox.addLayout(hbox, 1)
        label = QtGui.QLabel("You can copy paste this command line to get the same result with no graphical interface:", self.ui.centralWidget)
        vbox.addWidget(label)
        self.commandline = QtGui.QLineEdit(self.ui.centralWidget)
        self.commandline.setReadOnly(True)
        vbox.addWidget(self.commandline)

        self.ui.centralWidget.setLayout(vbox)
        self.setCentralWidget(self.ui.centralWidget)

    def skipMergesChanged(self, value):
        "This is heavy : we need to refetch everything"
        self.options.skipmerges = not not value
        self.dates = collect_data(self.repo.changelog, self.options)
        self.redraw()

    def showTagsChanged(self, value):
        self.options.showtags = not not value
        self.redraw()

    def uselinesChanged(self, value):
        "This is heavy : we need to refetch everything"
        self.options.uselines = not not value
        self.dates = collect_data(self.repo.changelog, self.options)
        self.redraw()

    def splitChanged(self, index):
        "This is heavy : we need to refetch everything"
        self.options.split = split_list[index]
        if index==0:
            # disable maxcaptions
            self.cwui.maxcaptionSpinBox.setEnabled(False)
            self.cwui.maxcaptionsLabel.setEnabled(False)
        else:
            # enable maxcaptions
            self.cwui.maxcaptionSpinBox.setEnabled(True)
            self.cwui.maxcaptionsLabel.setEnabled(True)
        self.dates = collect_data(self.repo.changelog, self.options)
        self.redraw()

    def timerangeUpdate(self, index):
        now = datetime.now()
        self.options.datemax = None
        if index==0:
            self.options.datemin = None
        elif index==1:
            self.options.datemin = now - timedelta(365)
        elif index==2:
            self.options.datemin = now - timedelta(30)
        elif index==3:
            self.options.datemin = now - timedelta(7)

        if index==4:
            # custom
            self.cwui.startDateEdit.setEnabled(True)
            self.cwui.endDateEdit.setEnabled(True)

            self.options.datemin = datetime.combine(self.cwui.startDateEdit.date().toPyDate(), time())
            self.options.datemax = datetime.combine(self.cwui.endDateEdit.date().toPyDate(), time())
        else:
            self.cwui.startDateEdit.setEnabled(False)
            self.cwui.endDateEdit.setEnabled(False)
            if self.options.datemin == None:
                self.cwui.startDateEdit.setDate(self.options.repo_datemin)
            else:
                self.cwui.startDateEdit.setDate(self.options.datemin)
            if self.options.datemax == None:
                self.cwui.endDateEdit.setDate(self.options.repo_datemax)
            else:
                self.cwui.endDateEdit.setDate(self.options.datemax)

    def timerangeChanged(self):
        "This is heavy : we need to refetch everything"
        index = self.cwui.timerangeComboBox.currentIndex()
        self.timerangeUpdate(index)
        self.dates = collect_data(self.repo.changelog, self.options)
        self.redraw()

    def maxcaptionChanged(self, newvalue):
        self.options.maxcaptions = newvalue
        self.redraw()

    def imageTitleChanged(self, newtext):
        self.options.imagetitle = newtext
        self.recomputeLineCommand()

    def filenameChanged(self, newtext):
        self.options.filename = newtext
        self.recomputeLineCommand()

    def redraw(self):
        draw_graph(self.fig, self.options, self.dates)
        self.canvas.draw()
        self.recomputeLineCommand()

    def recomputeLineCommand(self):
        line = "hg activity"
        if self.options.imagetitle != self.repo.root:
            line += " -t='%s'" % self.options.imagetitle
        if self.options.filename != 'activity.png':
            line += " -o='%s'" % self.options.filename
        if self.options.skipmerges:
            line += " --skipmerges"
        if self.options.showtags:
            line += " --showtags"
        if self.options.uselines:
            line += " --uselines"
        if self.options.split != "none":
            line += " --split=%s" % self.options.split
            if self.options.maxcaptions != 4:
                line += " --maxcaptions=%d" % self.options.maxcaptions
        if self.options.datemin != None:
            line += " --datemin=%s" % self.options.datemin.strftime("%Y-%m-%d")
        if self.options.datemax != None:
            line += " --datemax=%s" % self.options.datemax.strftime("%Y-%m-%d")
            
        self.commandline.setText(line)

    def about(self):
        msg = """
<h2>About</h2>
hgactivity is an extension for <a href="http://mercurial.selenic.com/">mercurial</a>
that creates an image displaying the activity for a repository.
<br/> <br/>
The official homepage is <a href="http://labs.freehackers.org/projects/hgactivity">http://labs.freehackers.org/projects/hgactivity</a>.
<br/> <br/>
More information can be found on the <a href="http://labs.freehackers.org/projects/hgactivity/wiki">wiki</a>
and on <a href="http://labs.freehackers.org/projects/hgactivity/wiki/documentation">the documentation page</a>.
<h2>Design & Coding</h2>
Thomas Capricelli <orzel@freehackers.org>
<br/>
<a href="http://www.freehackers.org/thomas/free-software/">http://www.freehackers.org/thomas/free-software/</a>
"""
        box = QtGui.QDialog(self)
        label = QtGui.QLabel(box)
        label.setOpenExternalLinks(True)
        label.setWordWrap(True)
        label.setWindowTitle("About hg activity (qt interface)")
        label.setText(msg)
        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(label)
        box.setLayout(vbox)
        button = QtGui.QPushButton("Ok", box)
        box.connect(button, QtCore.SIGNAL('clicked()'), box.accept)
        vbox.addWidget(button)
        box.exec_()

def displayQtGui(*kwargs):
    app = QtGui.QApplication([])
    window = MainWindow(*kwargs)
    window.resize(1300, 800)
    window.show()
    app.exec_()

""" 
TODO : options
    options.width = opts.get('width')
    options.height = opts.get('height')
    exclude = opts.get('exclude')
    aliases = opts.get('aliases')
"""
# vim: ai ts=4 sts=4 et sw=4
