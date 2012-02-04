#include "mainwindow.h"


/*! In the MainWindow constructor, we need to create
    all the actions and all the widgets. We call
    setupUI for this.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
    createActions();
    createMenus();
    connectSignalsSlots();

    signalMapper = new QSignalMapper(this);
    currentDocument = -1;

    //register the objects
    //actions.push_back(actionSelect);
    registerObject(new OvalNode);
    registerObject(new StickPerson);
    registerObject(new InteractionLine);

    //connect all the actions in the signalmapper to the one createObject slot.
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setPrototypeID(int)));

    //At this point, we need to add the actions created by registerObject
    //and put them into the menu structure and toolbar. Then
    //whenever one of the actions are triggered, the setPrototypeID function
    //is triggered with a prototype ID specified by the signalmapper
    /*
    for (int i=0; i<(int)actions.size(); i++) {

        Shapes_Connectors->addAction(actions.at(i));
        menuShapes->addAction(actions.at(i));

    }
    */

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
void MainWindow::registerObject(BaseNode* newPrototype)
{
    int newID;
    QAction* newAction;
    QPushButton* newButton;

    //register the prototype with the factory
    newID = NodeFactory::getInstance()->registerPrototype(newPrototype);

    //create the action
    newAction = new QAction(this);
    //set up the action with the right icon, text
    newAction->setText(newPrototype->getText());
    newAction->setIcon(QIcon(newPrototype->getIconPath()));
    newAction->setCheckable(true);

    //create the toolbar button
    /*
    newButton = new QPushButton(this);
    //set up the button with the right icon, text
    newButton->setText(newPrototype->getText());
    newButton->setIcon(QIcon(newPrototype->getIconPath()));
    newButton->setStyleSheet("text-align: left; font-size: 12px");
    newButton->setCheckable(true);
    newButton->setMinimumWidth(125);
    newButton->setObjectName("nodebutton");
    */

    //add the action and button to the signalmapper
    connect(newAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
    //connect(newButton, SIGNAL(clicked()), signalMapper, SLOT(map()));

    //add the action to the appropriate menu
    menuShapes->addAction(newAction);
    newToolbar->addAction(newAction);
    objectsActionGroup->addAction(newAction);

    //push the button and action back so we can access it later
    actions.push_back(newAction);
    //toolbarButtons.push_back(newButton);

    //map this button and action's signals with the prototype's ID.
    signalMapper->setMapping(newAction, newID);
    //signalMapper->setMapping(newButton, newID);

    //add the button to the appropriate frame layout, which is in the
    //the appropriate groupbox, which is in the mainToolbar
    /*
    if (newPrototype->isConnector() == true) {
        connectorsFrameLayout->addWidget(newButton);
        connectorsButtonGroup->addButton(newButton);
    } else {
        objectsFrameLayout->addWidget(newButton);
        objectsButtonGroup->addButton(newButton);
    }
    */
}


void MainWindow::setCurrentDocument(int index)
{
    /*assert(index >= -1);
    assert(index < (int)documents.size());
    assert(currentDocument >= -1);
    assert(currentDocument < (int)documents.size());

    //first disconnect the currently connected document
    if (currentDocument != -1) {
        disconnect(canvasWidget, 0, documents.at(currentDocument), 0);
        disconnect(documents.at(currentDocument), 0, canvasWidget, 0);
    }

    //Then connection the canvas to the new document
    currentDocument = index;
    connect(canvasWidget, SIGNAL(createObject(const QPoint &)), documents.at(currentDocument), SLOT(createObject(const QPoint &)));
    connect(canvasWidget, SIGNAL(moveSelectedObject(const QPoint &)), documents.at(currentDocument), SLOT(moveSelectedObject(const QPoint &)));
    connect(canvasWidget, SIGNAL(objectSelectionChange(const QPoint &)), documents.at(currentDocument), SLOT(setSelectedObject(const QPoint &)));
    connect(documents.at(currentDocument), SIGNAL(modelChanged()), canvasWidget, SLOT(update()));
    connect(canvasWidget, SIGNAL(redraw(QPainter&)), documents.at(currentDocument), SLOT(drawList(QPainter&)));
    connect(canvasWidget, SIGNAL(showPropertiesDialog()), documents.at(currentDocument), SLOT(showPropertiesDialog()));

    actionSelect->trigger();*/
}

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

    Canvas* canvas = canvases.at(canvasIndex);
    Document* document = documents.at(documentIndex);

    //first disconnect the currently connected document
    disconnect(canvas, 0, documents.at(canvas->getDocumentIndex()), 0);
    disconnect(document, 0, canvases.at(document->getCanvasIndex()), 0);

    //Then connect the canvas to the document
    connect(canvas, SIGNAL(createObject(const QPoint &)), document, SLOT(createObject(const QPoint &)));
    connect(canvas, SIGNAL(moveSelectedObject(const QPoint &)), document, SLOT(moveSelectedObject(const QPoint &)));
    connect(canvas, SIGNAL(objectSelectionChange(const QPoint &)), document, SLOT(setSelectedObject(const QPoint &)));
    connect(document, SIGNAL(modelChanged()), canvas, SLOT(update()));
    connect(canvas, SIGNAL(redraw(QPainter&)), document, SLOT(drawList(QPainter&)));
    connect(canvas, SIGNAL(showPropertiesDialog()), document, SLOT(showPropertiesDialog()));
    connect(canvas, SIGNAL(createConnectionPoint1(const QPoint &)), document, SLOT(createConnectionPoint1(const QPoint &)));
    connect(canvas, SIGNAL(createConnectionPoint2(const QPoint &)), document, SLOT(createConnectionPoint2(const QPoint &)));

    actionSelect->trigger();
}



/*! Mainwindow deconstructor
*/
MainWindow::~MainWindow()
{
    //Since we have a vector of pointers, we need to make sure
    //to free all of them manually.
    for (int i=0; i<(int)actions.size(); i++) {
        delete actions.at(i);
    }
    for (int i=0; i<(int)documents.size(); i++) {
        delete documents.at(i);
    }


}


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
    Shapes_Connectors = new QActionGroup(this);
    Shapes_Connectors -> setExclusive(true);
    actionDocument = new QAction(this);
    actionDocument->setText(tr("Help Document"));
    actionAbout = new QAction(this);
    actionAbout->setText(tr("About"));
    objectsActionGroup = new QActionGroup(this);
    objectsActionGroup->setExclusive(true);

    //Create the select action
    actionSelect = new QAction(this);
    actionSelect->setIcon(QIcon(":/Images/select.png"));
    actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    actionSelect->setCheckable(true);
    actionSelect->setText(tr("Select"));
    newToolbar->addAction(actionSelect);
    objectsActionGroup->addAction(actionSelect);
}

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
    menuTools->addAction(actionSelect);
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

    menuShapes->addAction(actionSelect);
}

void MainWindow::createToolbar()
{


/*
    QPushButton* select = new QPushButton(QIcon(":/Images/select.png"),"Select",this);
    select->setStyleSheet("text-align: left; font-size: 12px");
    select->setMinimumWidth(125);
    select->setCheckable(true);


    QPushButton* useCase = new QPushButton(QIcon(":/Images/oval.png"),"Use Case",this);
    useCase->setStyleSheet("text-align: left; font-size: 12px");
    useCase->setCheckable(true);
    useCase->setMinimumWidth(125);

    QPushButton* actor = new QPushButton(QIcon(":/Images/stickman.png"),"Actor",this);
    actor->setStyleSheet("text-align: left; font-size: 12px");
    actor->setCheckable(true);
    actor->setMinimumWidth(125);
    */


    //mainToolBar->addWidget(actor);
    //mainToolBar->addWidget(useCase);
//    mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

}

void MainWindow::createWidgets()
{
    //status bar
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);

    //canvas widgets
    //canvasWidget = new Canvas(this);
    //test = new Canvas(this);
    //canvasWidget->setObjectName(QString::fromUtf8("canvasWidget"));


    //tabwidgets
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setDocumentMode(true);
    //tabWidget->addTab(canvasWidget,"Use Case");
    //tabWidget->addTab(test,"Test");
    this->setCentralWidget(tabWidget);

    //toolbars
    /*mainToolBar = new QToolBar(this);
    mainToolBar->setMovable(false);
    mainToolBar->setMinimumWidth(125);
    this->addToolBar(Qt::LeftToolBarArea, mainToolBar);
    */

    newToolbar = new QToolBar(this);
    newToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addToolBar(Qt::RightToolBarArea, newToolbar);

    //the select button
    /*
    buttonSelect = new QPushButton(QIcon(":/Images/select.png"),"Select",this);
    buttonSelect->setStyleSheet("text-align: left; font-size: 12px");
    buttonSelect->setMinimumWidth(125);
    buttonSelect->setCheckable(true);
    buttonSelect->setObjectName("nodebutton");
    */

    //toolbar labels
    toolbarLabel = new QLabel;
    toolbarLabel->setText("Available Tools");
    toolbarLabel->setStyleSheet("padding-left: 13px; padding-top: 2px; font-size: 12px; font: bold");

    //toolbar groupboxes
    /*connectorsFrameLayout = new QVBoxLayout;
    connectorsFrameLayout->addWidget(buttonSelect);
    connectorsFrame = new QGroupBox;
    connectorsFrame->setLayout(connectorsFrameLayout);
    connectorsFrame->setTitle("Connectors");
    connectorsFrame->setAlignment(Qt::AlignCenter);
    connectorsFrame->setFlat(true);
    objectsFrameLayout = new QVBoxLayout;
    objectsFrameLayout->addWidget(buttonSelect);
    objectsFrame = new QGroupBox;
    objectsFrame->setLayout(objectsFrameLayout);
    objectsFrame->setTitle("Objects");
    objectsFrame->setAlignment(Qt::AlignCenter);
    objectsFrame->setFlat(true);
    objectsButtonGroup = new QButtonGroup;
    objectsButtonGroup->addButton(buttonSelect);
    objectsButtonGroup->setExclusive(true);
    */

    newToolbar->addWidget(toolbarLabel);
    //mainToolBar->addWidget(objectsFrame);
    //mainToolBar->addWidget(connectorsFrame);


/*
    toolbarLabel = new QLabel;
    toolbarLabel->setText("Available Tools");
    toolbarLabel->setStyleSheet("padding-left: 13px; padding-top: 2px; font-size: 12px; font: bold");



    createToolbar();
    */
}

void MainWindow::connectSignalsSlots()
{
    //Instead of using connectSlotsByName and dealing with that,
    //manually connect the slots
    //QMetaObject::connectSlotsByName(this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_triggered()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    connect(actionSave_As, SIGNAL(triggered()), this, SLOT(on_actionSave_As_triggered()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()));
    connect(actionPrint, SIGNAL(triggered()), this, SLOT(on_actionPrint_triggered()));
    connect(actionImport_Export, SIGNAL(triggered()), this, SLOT(on_actionImport_Export_triggered()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tabWidget_currentChanged(int)));

    connect(actionSelect, SIGNAL(triggered()), this, SLOT(on_actionSelect_triggered()));
    //connect(buttonSelect, SIGNAL(clicked()), this, SLOT(on_actionSelect_triggered()));

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

//Slot. It would probably be located in either the canvas or
//a seperate data structure, somewhere where it can have
//direct or indirect access to the vector of nodes.
void MainWindow::setPrototypeID(int prototypeID)
{
    //QMessageBox::information(this, "setPrototypeID: prototypeID", QString::number(prototypeID), QMessageBox::Ok);

    Canvas* currentCanvas;
    int canvasIndex;

    //Find the current canvas with the map
    canvasIndex = tabToCanvasMappings[tabWidget->currentIndex()];
    currentCanvas = canvases.at(canvasIndex);

    //notify the canvas that it should be in object mode
    currentCanvas->setMode(Canvas::Object);


    //we need to set the prototype id in currently
    //active document, so it knows what to create.
    documents.at(currentCanvas->getDocumentIndex())->setNewObjectID(prototypeID);
}

/*! This slot updates the currently active canvas's mode to Nothing. It
 *  uses a map of tab indices to canvas indices to find the current canvas.
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

/*! This slot first asks the user what type of diagram to create with a dialog.
 *  Then it create a new canvas and document, then connects them together.
 *  The canvas is added to a new tab and the tab-to-canvas map is updated.
 */
void MainWindow::on_actionNew_triggered()
{
    //dialog of UML types
    //dialogNew = new DialogNew;
    //dialogNew->show();
    QMessageBox::information(this, "pUML", "Creating a new generic diagram", QMessageBox::Ok);

    //Create the new document and canvas
    Document* newdoc = new Document;
    documents.push_back(newdoc);
    Canvas* newcanvas = new Canvas;
    canvases.push_back(newcanvas);

    //this might not be necessary
    newdoc->setCanvasIndex(canvases.size()-1);
    newcanvas->setDocumentIndex(documents.size()-1);

    //add the tab and update the map.
    int newTabIndex = tabWidget->addTab(newcanvas, "New Diagram");
    tabToCanvasMappings.insert(pair<int,int>(newTabIndex, canvases.size()-1));
    tabWidget->setCurrentIndex(newTabIndex);

    //setCurrentDocument(documents.size()-1);
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
