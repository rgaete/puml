#include "mainwindow.h"


/*! In the MainWindow constructor, we need to create
    all the actions, menus and widgets. registerObject is
    used to add prototypes to the NodeFactory and their buttons
    to the menus and toolbar. The new document slot is triggered.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
    createActions();
    createMenus();
    connectSignalsSlots();

    //signalMapper = new QSignalMapper(this);
    currentDocument = -1;

    //register the objects
    registerObject(new OvalObject);
    registerObject(new StickPersonObject);
    registerObject(new InteractionConnection);
    registerObject(new ClassConnection);
    registerObject(new ArrowConnection);

    this->resize(700,500);
    this->setWindowTitle(tr("Phunctional UML Editor"));

    //create a new document on launch
    on_actionNew_triggered();
}

//This is a helper function that registers an arbitrary Node* as a
//prototype in the factory. It then creates a new QAction based on
//data from the Node* and adds the action to signalmapper and
//actions.
//This function would be part of MainWindow, and actions and signalmapper
//would be both be member variables.
/*! Registers a protoype BaseNode* into NodeFactory, and creates a NodeAction from
    the prototype. It also adds the NodeAction into the menus and the toolbar.
*/
void MainWindow::registerObject(BaseNode* newPrototype)
{
    int newID;
    NodeAction *newAction;
    Canvas::DrawingMode drawingMode;

    //register the prototype with the factory
    newID = NodeFactory::getInstance()->registerPrototype(newPrototype);

    //Get the drawing mode for the action to hold
    if (newPrototype->isConnector() == true) {
        drawingMode = Canvas::Connection;
    } else {
        drawingMode = Canvas::Object;
    }

    //create the action with the mode, prototypeid, and parent
    newAction = new NodeAction(drawingMode, newID, this);

    //set up the action with the right icon, text
    newAction->setText(newPrototype->getText());
    newAction->setIcon(QIcon(newPrototype->getIconPath()));
    newAction->setCheckable(true);

    //connect the action to the NodeAction slots
    connect(newAction, SIGNAL(triggered(Canvas::DrawingMode,int)),
            this, SLOT(on_NodeAction_triggered(Canvas::DrawingMode, int)));

    //add the action to the appropriate menu
    if (drawingMode == Canvas::Connection) {
        menuConnectors->addAction(newAction);
    } else {
        menuShapes->addAction(newAction);
    }
    toolsActionGroup->addAction(newAction);
    mainToolBar->addAction(newAction);

    //push the action back so we can access it later (we don't actually access it later?)
    actions.push_back(newAction);
}

/*! Connects certain signals and slots of a canvas widget to signals and slots of
    a document. The document and canvas are specified with indices into canvases and
    documents. The signals from the canvas and the signals from the document are
    first disconnected before reconnecting.
*/
void MainWindow::connectCanvasWithDocument(int canvasIndex, int documentIndex)
{
    assert(canvasIndex >= 0);
    assert(canvasIndex < (int)canvases.size());
    assert(documentIndex >= 0);
    assert(documentIndex < (int)documents.size());
    assert(canvases.at(canvasIndex)->getDocumentIndex() >= 0);
    assert(canvases.at(canvasIndex)->getDocumentIndex() < documents.size());
    assert(documents.at(documentIndex)->getCanvasIndex() >= 0);
    assert(documents.at(documentIndex)->getCanvasIndex() < canvases.size());

    //get the canvas and document to connect
    Canvas* canvas = canvases.at(canvasIndex);
    Document* document = documents.at(documentIndex);

    //first disconnect the currently connected document
    disconnect(canvas, 0, documents.at(canvas->getDocumentIndex()), 0);
    disconnect(document, 0, canvases.at(document->getCanvasIndex()), 0);

    //create shortcuts for signals/slots
    QShortcut *delObject = new QShortcut(QKeySequence(QKeySequence::Delete),this);

    //Then connect the canvas to the document
    connect(canvas, SIGNAL(createObject(const QPoint &)), document, SLOT(createObject(const QPoint &)));
    connect(canvas, SIGNAL(moveSelectedObject(const QPoint &)), document, SLOT(moveSelectedObject(const QPoint &)));
    connect(canvas, SIGNAL(objectSelectionChange(const QPoint &)), document, SLOT(setSelectedObject(const QPoint &)));
    connect(document, SIGNAL(modelChanged()), canvas, SLOT(update()));
    connect(canvas, SIGNAL(redraw(QPainter&)), document, SLOT(drawList(QPainter&)));
    connect(canvas, SIGNAL(showPropertiesDialog()), document, SLOT(showPropertiesDialog()));
    connect(canvas, SIGNAL(removeObject()), document, SLOT(removeObject()));
    connect(delObject, SIGNAL(activated()), document, SLOT(removeObject()));
    connect(canvas, SIGNAL(createConnectionPoint1(const QPoint &)), document, SLOT(createConnectionPoint1(const QPoint &)));
    connect(canvas, SIGNAL(createConnectionPoint2(const QPoint &)), document, SLOT(createConnectionPoint2(const QPoint &)));

    //Go into selection mode
    actionSelect->trigger();
}

/*! This deconstructor frees up the memory held in any vectors that
    hold objects which don't have parents (basically any non-Qt objects)
*/
MainWindow::~MainWindow()
{
    //Since we have a vector of pointers, we need to make sure
    //to free all of them manually.
    for (int i=0; i<(int)documents.size(); i++) {
        assert(actions.at(i) != 0);
        delete documents.at(i);
    }
}

/*! Helps the constructor create the menu actions.
*/
void MainWindow::createActions()
{
    actionNew = new QAction(this);
    actionNew->setText(tr("New"));
    actionNew->setToolTip(tr("Create New pUML File"));
    actionOpen = new QAction(this);
    actionOpen->setText(tr("Open"));
    actionOpen->setToolTip(tr("Open a exsiting pUML file"));
    actionSave = new QAction(this);
    actionSave->setText(tr("Save"));
    actionSave->setToolTip(tr("Save current work into file"));
    actionSave_As = new QAction(this);
    actionSave_As->setText(tr("Save As.."));
    actionSave_As->setToolTip(tr("Save current work into another file"));
    actionPrint = new QAction(this);
    actionPrint->setText(tr("Print"));
    actionPrint->setToolTip(tr("Print the current work"));
    actionImport_Export = new QAction(this);
    actionImport_Export->setText(tr("Import/Export"));
    actionImport_Export->setToolTip(tr("Import/Export from/to other UML type file"));
    actionExit = new QAction(this);
    actionExit->setText(tr("Exit"));
    actionCopy = new QAction(this);
    actionCopy->setText(tr("Copy"));
    actionCut = new QAction(this);
    actionCut->setText(tr("Cut"));
    actionPaste = new QAction(this);
    actionPaste->setText(tr("Paste"));
    actionSelect_All = new QAction(this);
    actionSelect_All->setText(tr("Select All"));
    actionInverse_Select = new QAction(this);
    actionInverse_Select->setText(tr("Inverse Select"));
    actionDocument = new QAction(this);
    actionDocument->setText(tr("Help Document"));
    actionAbout = new QAction(this);
    actionAbout->setText(tr("About"));
    toolsActionGroup = new QActionGroup(this);
    toolsActionGroup->setExclusive(true);
    connectorsActionGroup = new QActionGroup(this);
    connectorsActionGroup->setExclusive(true);

    //Create the select action
    actionSelect = new QAction(this);
    actionSelect->setIcon(QIcon(":/Images/select.png"));
    actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    actionSelect->setCheckable(true);
    actionSelect->setText(tr("Select"));
    mainToolBar->addAction(actionSelect);
    toolsActionGroup->addAction(actionSelect);
}

/*! Helps the constructor create the menus.
*/
void MainWindow::createMenus()
{
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 673, 21));
    menuFile = new QMenu(menuBar);
    menuEdit = new QMenu(menuBar);
    menuTools = new QMenu(menuBar);
    menuShapes = new QMenu(menuTools);
    menuConnectors = new QMenu(menuTools);
    menuHelp = new QMenu(menuBar);
    this->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuTools->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_As);
    menuFile->addSeparator();
    menuFile->addAction(actionPrint);
    menuFile->addSeparator();
    menuFile->addAction(actionImport_Export);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionPaste);
    menuEdit->addSeparator();
    menuEdit->addAction(actionSelect_All);
    menuEdit->addAction(actionInverse_Select);
    menuTools->addAction(menuShapes->menuAction());
    menuTools->addAction(menuConnectors->menuAction());
    menuHelp->addAction(actionDocument);
    menuHelp->addSeparator();
    menuHelp->addAction(actionAbout);

    menuFile->setTitle(tr("File"));
    menuEdit->setTitle(tr("Edit"));
    menuTools->setTitle(tr("Tools"));
    menuShapes->setTitle(tr("Shapes"));
    menuConnectors->setTitle(tr("Connectors"));
    menuHelp->setTitle(tr("Help"));
}

/*! Helps the constructor create the widgets
*/
void MainWindow::createWidgets()
{
    //status bar
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);

    //tabwidgets
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    this->setCentralWidget(tabWidget);

    //toolbar
    mainToolBar = new QToolBar(this);
    mainToolBar->setMovable(false);
    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addToolBar(Qt::LeftToolBarArea, mainToolBar);

    //toolbar label
    toolbarLabel = new QLabel;
    toolbarLabel->setText("Diagram Tools");
    toolbarLabel->setStyleSheet("padding-left: 13px; padding-top: 2px; font-size: 12px; font: bold");
    mainToolBar->addWidget(toolbarLabel);
}

/*! Constructor helper, it connects all of the the various
    widgets and actions that MainWindow owns to all of the
    MainWindow's slots.
*/
void MainWindow::connectSignalsSlots()
{    
    //manually connect the slots
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_triggered()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    connect(actionSave_As, SIGNAL(triggered()), this, SLOT(on_actionSave_As_triggered()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()));
    connect(actionPrint, SIGNAL(triggered()), this, SLOT(on_actionPrint_triggered()));
    connect(actionImport_Export, SIGNAL(triggered()), this, SLOT(on_actionImport_Export_triggered()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tabWidget_currentChanged(int)));
    connect(actionSelect, SIGNAL(triggered()), this, SLOT(on_actionSelect_triggered()));

    /* list of slots
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionPrint_triggered();
    void on_actionImport_Export_triggered();
    void on_actionExit_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionSelect_triggered();
    void on_actionSelect_All_triggered();
    void on_actionInverse_Select_triggered();
    void on_actionCircle_toggled(bool arg1);
    void on_actionDiamond_toggled(bool arg1);
    void on_actionRectangle_toggled(bool arg1);
    void on_actionStickMan_toggled(bool arg1);
    void on_actionArrow_toggled(bool arg1);
    void on_actionLine_toggled(bool arg1);
    void on_actionDotted_Line_toggled(bool arg1);
    void on_actionTile_Horizontally_toggled(bool arg1);
    void on_actionTile_Vertically_toggled(bool arg1);
    void on_actionCascade_toggled(bool arg1);
    void on_actionDocument_triggered();
    void on_actionAbout_triggered();
    */
}

/*! This slot gets triggered whenever one of the NodeActions are triggered,
    which could be from the toolbar or menu. Those NodeActions hold
    the drawingMode and prototypeID. This slot then puts the canvas and
    document into the right modes and sets the right id's.
*/
void MainWindow::on_NodeAction_triggered(Canvas::DrawingMode drawingMode, int prototypeID)
{
    //QMessageBox::information(this, "setPrototypeID: prototypeID", QString::number(prototypeID), QMessageBox::Ok);

    Canvas* currentCanvas;
    int canvasIndex;

    //Find the current canvas with the map
    canvasIndex = tabToCanvasMappings[tabWidget->currentIndex()];
    currentCanvas = canvases.at(canvasIndex);

    //notify the canvas that it should be in object mode
    currentCanvas->setMode(drawingMode);

    //we need to set the prototype id in currently
    //active document, so it knows what to create.
    documents.at(currentCanvas->getDocumentIndex())->setNewObjectID(prototypeID);
}

/*! This slot updates the currently active canvas's mode to Nothing. It
 *  uses a map of tab indices to canvas indices to find the current canvas.
 *  @todo Try move the mappings into the tabs themselves or into the documents
          to eleminate the need for a map.
 */
void MainWindow::on_actionSelect_triggered() {
    /* The old way with a static cast (...shiver...)
    Canvas* canvas;
    canvas = static_cast<Canvas*>(tabWidget->currentWidget());
    canvas->setMode(Canvas::Nothing);
    */

    /* The new way with the map :) */
    int canvasIndex;
    canvasIndex = tabToCanvasMappings[tabWidget->currentIndex()];
    canvases.at(canvasIndex)->setMode(Canvas::Nothing);
}

/*! Creates a new diagram file.
 *  This slot first asks the user what type of diagram to create with a dialog.
 *  Then it create a new canvas and document, then connects them together.
 *  The canvas is added to a new tab and the tab-to-canvas map is updated.
 *  @todo This should also add the diagram to the current project.
 */
void MainWindow::on_actionNew_triggered()
{
    //dialog of UML types
    //dialogNew = new DialogNew;
    //dialogNew->show();
    //QMessageBox::information(this, "pUML", "Creating a new generic diagram", QMessageBox::Ok);

    // this is the new dialogue, hopefully
    ConfigDialog dialog;
    dialog.exec();

    //Create the new document and canvas
    Document* newdoc = new Document;
    documents.push_back(newdoc);
    Canvas* newcanvas = new Canvas;
    canvases.push_back(newcanvas);

    //These member variables aren't used in any other function
    //they should either be removed or the map should be removed
    //and something like this should take it's place.
    newdoc->setCanvasIndex(canvases.size()-1);
    newcanvas->setDocumentIndex(documents.size()-1);

    //add the tab and update the map.
    int newTabIndex = tabWidget->addTab(newcanvas, "New Diagram");
    tabToCanvasMappings.insert(pair<int,int>(newTabIndex, canvases.size()-1));
    tabWidget->setCurrentIndex(newTabIndex);

    //Connect the new canvas with the new document.
    connectCanvasWithDocument(canvases.size()-1, documents.size()-1);
}











/*! This slot receives the currentChanged signal from the tabWidget.
 *  It should reupdate the toolbar with the previously selected tool
 *  and only the legal buttons for the diagram.
 */
void MainWindow::on_tabWidget_currentChanged(int newIndex)
{
    actionSelect->trigger();
    /*
    //An attempt at making the toolbar update with the last selected tool...
    Canvas* canvas;
    Document* document;
    int documentIndex;
    Canvas::DrawingMode drawingMode;

    canvas = static_cast<Canvas*>(tabWidget->widget(newIndex));
    documentIndex = canvas->getDocumentIndex();
    document = documents.at(documentIndex);
    drawingMode = canvas->getMode();

    if (drawingMode == Canvas::Nothing) {

    } else {
        int newObjectID;
        QAction* lastAction;

        newObjectID = document->getNewObjectID();
        lastAction = static_cast<QAction*>(signalMapper->mapped(document->getNewObjectID()));

        lastAction->trigger();
    }

*/

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Document"),  tr("XML files (*.xml)"));

    // write the loading file function here with the fileName
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       tr("XML files (*.xml)"));

    // write the saving file function here with the fileName
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As File"),
                       tr("XML files (*.xml)"));

    // write the saving as file function here with the fileName
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter* printer = new QPrinter;
    QPrintDialog printDialog(printer,this);
    if (printDialog.exec() == QDialog::Accepted) {
        // print ...
    }
    delete printer;

}

void MainWindow::on_actionImport_Export_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionCut_triggered()
{

}

void MainWindow::on_actionPaste_triggered()
{

}

void MainWindow::on_actionSelect_All_triggered()
{

}

void MainWindow::on_actionInverse_Select_triggered()
{

}

void MainWindow::on_actionTile_Horizontally_toggled(bool arg1)
{

}

void MainWindow::on_actionTile_Vertically_toggled(bool arg1)
{

}

void MainWindow::on_actionCascade_toggled(bool arg1)
{

}

void MainWindow::on_actionDocument_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About pUML"),
      tr("<p>The <b>pUML</b> project is the CS383 Software Engeering I Class"
         " final project.</p><p> It was developed by seven awesome students during"
         " their spare time. The development tools is provided by Nokia -- Qt"
         " and Google code repository.</p>"));
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
