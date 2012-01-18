#!/usr/bin/env python
# -*- coding: utf-8
# vim: set fileencoding=utf-8

# Copyright 2008-2011 Thomas Capricelli <orzel@freehackers.org>
# mercurial extension released under the GNU General Public Licence (GPLv2)

#
# To use this extension, add something like this to your ~/.hgrc :
#
# activity=/home/orzel/hg/hgactivity/activity.py
#
# (using the atual path, of course)
#
# will appear in 'hg --help'
'''create an image file displaying the activity of the current repository'''

from os import path
from datetime import datetime

from mercurial import demandimport

demandimport.ignore.extend([
        'matplotlib',
        'matplotlib.dates',
        'matplotlib.ticker',
        'matplotlib.units',
        'matplotlib.collections',
        'matplotlib.axis',
        'matplotlib.pyplot',
        'matplotlib.contour',
        'pkg_resources',
        'resource_stream',
        ])

# demandimport is evil, breaks everything, is impossible to fix, nobody
# will help you on irc, and it will probably try to eat your children as
# well. Disable it.
demandimport.disable()

from mercurial.i18n import gettext as _
from data import collect_data

class UiException(Exception):
    def __init__(self, message):
        self.message = message
    def __str__(self):
        return repr(self.message)

split_list = ['none', 'authors', 'files', 'branches', 'directories']

#
# Extension callback
#
def activity(ui, repo, **opts):
    # The doc string below will show up in 'hg activity --help'
    """
    Create a file called activity.png displaying the activity of the current
    repository

    By default, the activity is computed using the number of commits. There
    is an option to consider instead the number of lines modified in the
    changesets (--uselines).

    Most options are self explanatory.
    The map file format used to specify aliases is fairly simple:
    <alias name>; <actual name>
    This file is only used when --split=authors is used.

    The name listed after the option --exclude are those found in the
    mercurial repository. That is, before the map file is applied.
    """
    # do it
    try:
        options = check_options(repo, opts)
        ui.write('There are %d changesets\n' % options.length)

        # do something with this data:
        if options.mode=='display':
            try:
                import matplotlib.pyplot as plt
            except:
                raise UiException('you need matplotlib in your python path in order to use the hg activity extension.')
            from draw import draw_graph

            # harvest data
            dates_tab = collect_data(repo.changelog, options)
            if len(dates_tab)<1 or not options.length:
                raise UiException('no data available with those options.')

            fig = plt.figure() 
            draw_graph(fig, options, dates_tab)
            plt.show()
        elif options.mode=='file':
            try:
                from matplotlib.figure import Figure
                from matplotlib.backends.backend_agg import FigureCanvasAgg
            except:
                raise UiException('you need matplotlib in your python path in order to use the hg activity extension.')
            from draw import draw_graph

            # harvest data
            dates_tab = collect_data(repo.changelog, options)
            if len(dates_tab)<1 or not options.length:
                raise UiException('no data available with those options.')

            fig = Figure()
            canvas = FigureCanvasAgg(fig)
            draw_graph(fig, options, dates_tab)
            fig.set_dpi(100)
            fig.set_size_inches(options.width/100.0,options.height/100.0)
            canvas.print_figure(options.filename)
            ui.status('Created the file \'%s\'\n' % options.filename)
        elif options.mode=='gui':
            from mode_qt import displayQtGui
            displayQtGui(repo, options)
        else:
            raise UiException('unknown mode %s', options.mode)
            
    except UiException, error:
        from sys import exit
        ui.warn("Hg activity, checking options: %s\n" % error.message)
        exit(1)

cmdtable = {
    # cmd name        function call
    'activity': (activity,
                 # see mercurial/fancyopts.py for all of the command
                 # flag options.
                 [
                 ('', 'mode', 'file', _("Specifiy the mode for reporting the activity, one of: 'file' : create a file, 'display' : display inside a graphical window, or 'gui' : full interface from which you can change options (requires PyQt/Qt)"), 'string'),
                 ('', 'split', 'none', _("Specifiy if the graph should be splitted by %s.") % ", ".join(["'%s'"%s for s in split_list]), 'string'),
                 ('o', 'filename', 'activity.png', _('name of the file created (only with mode=file)'), 'string'),
                 ('w', 'width', 800, _('Width of the graph in pixels'), 'integer'),
                 ('h', 'height', 600, _('Height of the graph in pixels'), 'integer'),
                 ('', 'datemin', '', _('Start date of the graph (yyyy-mm-dd)'), 'string'),
                 ('', 'datemax', '', _('End date of the graph (yyyy-mm-dd)'), 'string'),
                 ('', 'maxcaptions', 4, _('Maximum number of captions (when using --split).'), 'integer'),
                 ('x', 'exclude', '', _('Comma-separated list of authors to ignore.'), 'string'),
                 ('', 'aliases', '', _('file with email aliases'), 'string'),
                 ('', 'skipmerges', False, _('Do not consider merge commits')),
                 ('l', 'uselines', False, _('Use the number of lines modified instead of the number of commits')),
                 ('', 'showtags', False, _('Display tags on the X axis')),
                 ('t', 'imagetitle', '', _('Title (default to repository path)'), 'string'),
                 ],
                 'hg activity [OPTION]... ')
}

class Options:
    pass

def check_options(repo, opts):
    # parse options
    options = Options()
    options.repo = repo

    options.filename = opts.get('filename')
    options.width = opts.get('width')
    if options.width<50: options.width=50
    options.height = opts.get('height')
    if options.height<30: options.height=30
    options.skipmerges = opts.get('skipmerges')
    options.maxcaptions = opts.get('maxcaptions')
    if options.maxcaptions<1 or options.maxcaptions>30:
        raise UiException("The --maxcaption value must be set between 1 and 30, included")
        
    options.uselines = opts.get('uselines')
    options.showtags = opts.get('showtags')

    options.imagetitle = opts.get('imagetitle').decode("utf-8")
    if options.imagetitle=='':
        options.imagetitle = repo.root

    if opts.get('datemin'):
        options.datemin = datetime.strptime(opts.get('datemin'), '%Y-%m-%d')
        if (options.datemin<datetime(1900, 1, 1)):
            raise UiException("invalid --datemin value. The minimal accepted value is 1900-01-01")
    else:
        options.datemin = None

    if opts.get('datemax'):
        options.datemax = datetime.strptime(opts.get('datemax'), '%Y-%m-%d')
    else:
        options.datemax = None

    exclude = opts.get('exclude')
    if exclude:
        options.exclude = exclude.split(',')
    else:
        options.exclude = []

    if hasattr(repo.changelog,'count'):
        options.length = repo.changelog.count() # mercurial 1.0.2 and previous
    else:
        options.length = len(repo.changelog) # mercurial 1.1 and up

    # handle 'mode'
    options.mode = opts.get('mode')
    if not options.mode in ['file', 'display', 'gui']:
        raise UiException('unknown mode \'%s\'.' % options.mode)

    # handle 'split'
    options.split = opts.get('split')
    if not options.split in split_list:
        raise UiException('unknown split option \'%s\'.' % options.split)

    # handle aliases
    options.amap = {}
    aliases = opts.get('aliases')
    if aliases:
        if path.exists(aliases):
            try:
                for l in open(aliases, 'r'):
                    l = l.strip()
                    alias, actual = l.split()
                    options.amap[alias.strip()] = actual.strip()
            except:
                raise UiException('some problem was found parsing the alias file \'%s\'.' % aliases)
        else:
            raise UiException('alias file \'%s\' does not exist.' % aliases)

    # fetch tags
    options.tags = map_tags(repo, options)

    # compute min/max time for repo
    a,b,cl = None, None, repo.changelog
    for i in cl:
        node = cl.read(cl.node(i))
        # find out date and filter
        date = datetime.fromtimestamp(node[2][0])
        if a==None or date<a: a = date
        if b==None or date>b: b = date
    options.repo_datemin = a
    options.repo_datemax = b
    # print "repo range", options.repo_datemin, options.repo_datemax
    # ok, done
    return options

# TODO : we should keep them all here, and filters them out only when
# displaying the graph
def map_tags(repo, options):
    tags= []
    for tagname, rev in repo.tags().items():
        if tagname=='tip': continue
        date = datetime.fromtimestamp( repo.changectx(rev).date()[0])
        if options.datemin!=None and date<options.datemin:
            continue
        if options.datemax!=None and date>options.datemax:
            continue
        tags.append((date,tagname))
    tags.sort()
    return tags

# vim: ai ts=4 sts=4 et sw=4
