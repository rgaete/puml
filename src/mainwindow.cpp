#include "mainwindow.h"


/*! In the MainWindow constructor, we need to create
    all the actions and all the widgets. We call
    setupUI for this.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    createWidgets();
    connectSignalsSlots();

    signalMapper = new QSignalMapper(this);
    currentDocument = -1;

    //register the objects
    actions.push_back(actionSelect);
    registerObjectWithFactory(new OvalNode);
    registerObjectWithFactory(new StickPerson);

    //connect all the actions in the signalmapper to the one createObject slot.
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setPrototypeID(int)));

    //At this point, we need to add the actions created by registerObject
    //and put them into the menu structure and toolbar. Then
    //whenever one of the actions are triggered, the setPrototypeID function
    //is triggered with a prototype ID specified by the signalmapper
    for (int i=0; i<(int)actions.size(); i++) {
        Shapes_Connectors->addAction(actions.at(i));
//        mainToolBar->addAction(actions.at(i));
        menuShapes->addAction(actions.at(i));

    }

    this->resize(800,500);
    this->setWindowTitle(tr("Phunctional UML Editor"));

    //create a new document on launch
    on_actionNew_triggered();
}

//This is a helper function that registers an arbitrary Node* as a
//prototype in the factory. It then creates a new QAction based on
//data from the Node* and adds the action to signalmapper and
//actions.
//This function would be part of MainWindow, and actions and signalmapper
//would be both be member variables. Factory would probably be a singleton
void MainWindow::registerObjectWithFactory(BaseNode* newPrototype)
{
    int newID;
    QAction* newAction;

    //register the prototype
    newID = NodeFactory::getInstance()->registerPrototype(newPrototype);
    //create the action
    newAction = new QAction(this);
    //set up the action with the right icon, text
    newAction->setText(newPrototype->getText());
    newAction->setIcon(QIcon(newPrototype->getIconPath()));
    newAction->setCheckable(true);
    //add this action to the signalmapper
    connect(newAction, SIGNAL(triggered()), signalMapper, SLOT(map()));
    //add this action to the actions vector so we can access it later
    actions.push_back(newAction);
    //map this signal with the prototype's ID.
    signalMapper->setMapping(newAction, newID);
}

void MainWindow::setCurrentDocument(int index)
{
    assert(index >= -1);
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

    actionSelect->trigger();
}

//Slot. It would probably be located in either the canvas or
//a seperate data structure, somewhere where it can have
//direct or indirect access to the vector of nodes.
void MainWindow::setPrototypeID(int prototypeID)
{
    //QMessageBox::information(this, "setPrototypeID: prototypeID", QString::number(prototypeID), QMessageBox::Ok);
    assert(currentDocument >= -1);
    assert(currentDocument < (int)documents.size());

    //notify the canvas that it should be in object mode
    canvasWidget->setMode(Canvas::Object);

    //we need to set the prototype id in currently
    //active document, so it knows what to create.
    if (currentDocument != -1) {
        documents.at(currentDocument)->setNewObjectID(prototypeID);
    }


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


    /*
    actionCircle = new QAction(this);
    actionCircle->setIcon(QIcon(":/Images/oval.png"));
    // all of these jpg and jpeg files are set for the directory that I put them in, they need to be changed in order to work on anyone elses computer
    // not sure if the line below is needed anymore
    actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
    actionCircle->setCheckable(true);
    Shapes_Connectors->addAction(actionCircle);

    actionDiamond = new QAction(this);
    actionDiamond->setIcon(QIcon(":/Images/diamond.png"));
    // all of these jpg and jpeg files are set for the directory that I put them in, they need to be changed in order to work on anyone elses computer
    // not sure if the line below is needed anymore
    actionDiamond->setObjectName(QString::fromUtf8("actionDiamond"));
    actionDiamond->setCheckable(true);
    Shapes_Connectors->addAction(actionDiamond);

    actionRectangle = new QAction(this);
    actionRectangle->setIcon(QIcon(":/Images/rectangle.png"));
    actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
    actionRectangle->setCheckable(true);
    Shapes_Connectors->addAction(actionRectangle);

    actionSquare = new QAction(this);
    actionSquare->setIcon(QIcon(":/Images/square.png"));
    actionSquare->setObjectName(QString::fromUtf8("actionSquare"));
    actionSquare->setCheckable(true);
    Shapes_Connectors->addAction(actionSquare);

    actionArrow = new QAction(this);
    actionArrow->setObjectName(QString::fromUtf8("actionArrow"));
    actionArrow->setCheckable(true);
    Shapes_Connectors->addAction(actionArrow);

    actionLine = new QAction(this);
    actionLine->setObjectName(QString::fromUtf8("actionLine"));
    actionLine->setCheckable(true);
    Shapes_Connectors->addAction(actionLine);

    actionDotted_Line = new QAction(this);
    actionDotted_Line->setObjectName(QString::fromUtf8("actionDotted_Line"));
    actionDotted_Line->setCheckable(true);
    Shapes_Connectors->addAction(actionDotted_Line);
*/


    //menuEdit->setDisabled(true);
    //menuTools->setDisabled(true);
    //menuShapes->setDisabled(true);
    //menuWindow->setDisabled(true);


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

    actionSelect = new QAction(this);
    actionSelect->setIcon(QIcon(":/Images/select.png"));
    actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    actionSelect->setCheckable(true);
    actionSelect->setText(tr("Select"));
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
}

void MainWindow::createToolbar()
{
    mainToolBar = new QToolBar(this);
    this->addToolBar(Qt::LeftToolBarArea, mainToolBar);
    mainToolBar->setMovable(false);
    mainToolBar->setMinimumWidth(150);
}

void MainWindow::createWidgets()
{
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);

    canvasWidget = new Canvas(this);
    canvasWidget->setObjectName(QString::fromUtf8("canvasWidget"));
    this->setCentralWidget(canvasWidget);

    createToolbar();
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
    connect(actionSelect, SIGNAL(toggled(bool)), this, SLOT(on_actionSelect_toggled(bool)));
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

void MainWindow::on_actionNew_triggered()
{
    //dialog of UML types
    //dialogNew = new DialogNew;
    //dialogNew->show();
    QMessageBox::information(this, "pUML", "Creating a new generic diagram", QMessageBox::Ok);

    Document* newdoc = new Document;
    documents.push_back(newdoc);

    setCurrentDocument(documents.size()-1);
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

void MainWindow::on_actionSelect_toggled(bool arg1) {
    if (arg1 == true) {
        canvasWidget->setMode(Canvas::Nothing);
    }
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
