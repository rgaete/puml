// Copyright (C) 2011-2012 pUML Group

#include "./mainwindow.h"
#include <utility>
#include <vector>
#include <fstream>  // NOLINT
#include <algorithm>
#include <string>
#include <iostream>
// I'm not sure why cpplint.py is insisting that <vector> be included
// when it exists in mainwindow.h...

// In the future, we might want to consider something other than a stream?
using std::ifstream;  // NOLINT
using std::vector;
using std::string;

/*! In the MainWindow constructor, we need to create
  all the actions, menus and widgets. registerObject is
  used to add prototypes to the NodeFactory and their buttons
  to the menus and toolbar. The new document slot is triggered.
*/
MainWindow::MainWindow(QWidget *parent)
           :QMainWindow(parent) {
  createWidgets();
  createActions();
  createMenus();
  connectSignalsSlots();

  // signalMapper = new QSignalMapper(this);
  currentDocument = -1;

  // Use case objects
  registerObject(new OvalObject);
  registerObject(new StickPersonObject);
  registerObject(new InteractionConnection);
  registerObject(new ExtendsConnection);
  registerObject(new IncludesConnection);

  // statechart objects
  registerObject(new StateObject);
  registerObject(new InitialStateObject);
  registerObject(new FinalStateObject);
  registerObject(new TransitionConnection);

  // class objects
  registerObject(new ClassBoxObject);
  registerObject(new ClassConnection);
  registerObject(new InheritanceConnection);
  registerObject(new AggregationConnection);

  // register collab objects
  registerObject(new StickPersonCollabObject);
  registerObject(new BoxCollabObject);
  registerObject(new MultiBoxCollabObject);
  registerObject(new CollabConnection);
  registerObject(new CollabSelfConnection);

  this->resize(700, 500);
  this->setWindowTitle(tr("Phunctional UML Editor"));

  // Show the Open/New dialog
  openFileNewDialog(ConfigDialog::OpenAndNew);
}

// This is a helper function that registers an arbitrary Node* as a
// prototype in the factory. It then creates a new QAction based on
// data from the Node* and adds the action to signalmapper and
// actions.
// This function would be part of MainWindow, and actions and signalmapper
// would be both be member variables.
/*! Registers a protoype BaseNode* into NodeFactory, and creates a NodeAction
 * from the prototype. It also adds the NodeAction into the menus and the
 * toolbar.
 */
void MainWindow::registerObject(BaseNode* newPrototype) {
  int newID;
  NodeAction *newAction;
  Canvas::DrawingMode drawingMode;
  BaseNode::DiagramType diagramType;

  // register the prototype with the factory
  newID = NodeFactory::getInstance()->registerPrototype(newPrototype);

  // Get the drawing mode for the action to hold
  if (newPrototype->isConnector() == true) {
    drawingMode = Canvas::Connection;
  } else {
    drawingMode = Canvas::Object;
  }

  // get the diagram the node is in
  diagramType = newPrototype->getDiagramType();

  // create the action with the mode, prototypeid, and parent
  newAction = new NodeAction(drawingMode, newID, diagramType, this);

  // set up the action with the right icon, text
  newAction->setText(newPrototype->getText());
  newAction->setIcon(QIcon(newPrototype->getIconPath()));
  newAction->setCheckable(true);

  // connect the action to the NodeAction slots
  connect(newAction, SIGNAL(triggered(Canvas::DrawingMode, int)),
          this, SLOT(on_NodeAction_triggered(Canvas::DrawingMode, int)));

  // add the action to the appropriate menu
  if (drawingMode == Canvas::Connection) {
    menuConnectors->addAction(newAction);
  } else {
    menuShapes->addAction(newAction);
  }

  toolsActionGroup->addAction(newAction);
  mainToolBar->addAction(newAction);

  // push the action back so we can access it later
  actions.push_back(newAction);
}

/*! Connects certain signals and slots of a canvas widget to signals and slots
 *  of a document. The document and canvas are specified with indices into
 *  canvases and documents. The signals from the canvas and the signals from
 *  the document are first disconnected before reconnecting.
*/
void MainWindow::connectCanvasWithDocument(int canvasIndex, int documentIndex) {
  assert(canvasIndex >= 0);
  assert(canvasIndex < static_cast<int>(canvases.size()));
  assert(documentIndex >= 0);
  assert(documentIndex < static_cast<int>(documents.size()));
  assert(canvases.at(canvasIndex)->getDocumentIndex() >= 0);
  assert(canvases.at(canvasIndex)->getDocumentIndex() < static_cast<int>(documents.size()));  // NOLINT
  assert(documents.at(documentIndex)->getCanvasIndex() >= 0);
  assert(documents.at(documentIndex)->getCanvasIndex() < static_cast<int>(canvases.size()));  // NOLINT

  // save some convenience variables
  Canvas* canvas = canvases.at(canvasIndex);
  Document* document = documents.at(documentIndex);

  // first disconnect the currently connected document
  disconnect(canvas, 0, documents.at(canvas->getDocumentIndex()), 0);
  disconnect(document, 0, canvases.at(document->getCanvasIndex()), 0);

  // create shortcuts for signals/slots
  QShortcut *delObject = new QShortcut(QKeySequence(QKeySequence::Delete), this);

  // Then connect the canvas to the document
  connect(canvas, SIGNAL(createObject(const QPoint &)),
          document, SLOT(createObject(const QPoint &)));
  connect(canvas, SIGNAL(moveSelectedObject(const QPoint &)),
          document, SLOT(moveSelectedObject(const QPoint &)));
  connect(canvas, SIGNAL(objectSelectionChange(const QPoint &)),
          document, SLOT(setSelectedObject(const QPoint &)));
  connect(document, SIGNAL(modelChanged()), canvas, SLOT(update()));
  connect(canvas, SIGNAL(redraw(QPainter&)),
          document, SLOT(drawList(QPainter&)));
  connect(canvas, SIGNAL(showPropertiesDialog()),
          document, SLOT(showPropertiesDialog()));
  connect(canvas, SIGNAL(removeObject()),
          document, SLOT(removeObject()));
  connect(delObject, SIGNAL(activated()), document, SLOT(removeObject()));
  connect(canvas, SIGNAL(createConnectionPoint1(const QPoint &)),
          document, SLOT(createConnectionPoint1(const QPoint &)));
  connect(canvas, SIGNAL(createConnectionPoint2(const QPoint &)),
          document, SLOT(createConnectionPoint2(const QPoint &)));
  connect(canvas, SIGNAL(changeSecondConnectionPointHint(const QPoint &)),
          document, SLOT(changeSecondConnectionPointHint(const QPoint &)));
  connect(canvas, SIGNAL(selectNothing()),
          this, SLOT(setSelect()));
  connect(toolsActionGroup, SIGNAL(triggered(QAction*)),
          canvas, SLOT(deselect()));
  connect(connectorsActionGroup, SIGNAL(triggered(QAction*)),
          canvas, SLOT(deselect()));

  // Set the currentDocument flag
  currentDocument = documentIndex;

  // Go into selection mode
  actionSelect->trigger();
}



/*! This deconstructor frees up the memory held in any vectors that
  hold objects which don't have parents (basically any non-Qt objects)
*/
MainWindow::~MainWindow() {
  // Since we have a vector of pointers, we need to make sure
  // to free all of them manually.
  for (int i = 0; i < static_cast<int>(documents.size()); i++) {
    assert(actions.at(i) != 0);
    delete documents.at(i);
  }
}

/*! Helps the constructor create the menu actions.
*/
void MainWindow::createActions() {
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
  actionImport_Export->setToolTip(
      tr("Import/Export from/to other UML type file"));
  actionImport_Export->setEnabled(false);
  actionExit = new QAction(this);
  actionExit->setText(tr("Exit"));
  actionCopy = new QAction(this);
  actionCopy->setText(tr("Copy"));
  actionCopy->setEnabled(false);
  actionCut = new QAction(this);
  actionCut->setText(tr("Cut"));
  actionCut->setEnabled(false);
  actionPaste = new QAction(this);
  actionPaste->setText(tr("Paste"));
  actionPaste->setEnabled(false);
  actionSelect_All = new QAction(this);
  actionSelect_All->setText(tr("Select All"));
  actionSelect_All->setEnabled(false);
  actionInverse_Select = new QAction(this);
  actionInverse_Select->setText(tr("Inverse Select"));
  actionInverse_Select->setEnabled(false);
  actionDocument = new QAction(this);
  actionDocument->setText(tr("Help Document"));
  actionDocument->setEnabled(false);
  actionAbout = new QAction(this);
  actionAbout->setText(tr("About"));
  actionAbout->setEnabled(false);
  actionSendForwards = new QAction(this);
  actionSendForwards->setText("Send Forwards");
  actionSendBackwards = new QAction(this);
  actionSendBackwards->setText("Send Backwards");
  actionSendToBack = new QAction(this);
  actionSendToBack->setText("Send To Back");
  actionSendToFront = new QAction(this);
  actionSendToFront->setText("Send To Front");

  toolsActionGroup = new QActionGroup(this);
  toolsActionGroup->setExclusive(true);
  connectorsActionGroup = new QActionGroup(this);
  connectorsActionGroup->setExclusive(true);

  // Create the select action
  actionSelect = new QAction(this);
  actionSelect->setIcon(QIcon(":/Images/select.png"));
  actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
  actionSelect->setCheckable(true);
  actionSelect->setText(tr("Select"));
  mainToolBar->addAction(actionSelect);
  toolsActionGroup->addAction(actionSelect);
  // diagram_UseCaseActionGroup->addAction(actionSelect);
  // diagram_ClassActionGroup->addAction(actionSelect);
}

/*! Helps the constructor create the menus.
*/
void MainWindow::createMenus() {
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
  menuEdit->addAction(actionSendForwards);
  menuEdit->addAction(actionSendBackwards);
  menuEdit->addAction(actionSendToBack);
  menuEdit->addAction(actionSendToFront);
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
void MainWindow::createWidgets() {
  // status bar
  statusBar = new QStatusBar(this);
  this->setStatusBar(statusBar);

  // tabwidgets
  tabWidget = new QTabWidget(this);
  tabWidget->setTabsClosable(true);
  tabWidget->setMovable(true);
  this->setCentralWidget(tabWidget);

  // toolbar
  mainToolBar = new QToolBar(this);
  mainToolBar->setMovable(false);
  mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  this->addToolBar(Qt::LeftToolBarArea, mainToolBar);

  // toolbar label
  toolbarLabel = new QLabel;
  toolbarLabel->setText("Diagram Tools");
  toolbarLabel->setStyleSheet(
      "padding-left: 13px; padding-top: 2px; font-size: 12px; font: bold");
  mainToolBar->addWidget(toolbarLabel);
}

/*! Constructor helper, it connects all of the the various
  widgets and actions that MainWindow owns to all of the
  MainWindow's slots.
*/
void MainWindow::connectSignalsSlots() {
  // manually connect the slots
  connect(actionNew, SIGNAL(triggered()),
          this, SLOT(on_actionNew_triggered()));
  connect(actionOpen, SIGNAL(triggered()),
          this, SLOT(on_actionOpen_triggered()));
  connect(actionSave, SIGNAL(triggered()),
          this, SLOT(on_actionSave_triggered()));
  connect(actionSave_As, SIGNAL(triggered()),
          this, SLOT(on_actionSave_As_triggered()));
  connect(actionExit, SIGNAL(triggered()),
          this, SLOT(on_actionExit_triggered()));
  connect(actionPrint, SIGNAL(triggered()),
          this, SLOT(on_actionPrint_triggered()));
  connect(actionImport_Export, SIGNAL(triggered()),
          this, SLOT(on_actionImport_Export_triggered()));
  connect(tabWidget, SIGNAL(currentChanged(int)),  // NOLINT
          this, SLOT(on_tabWidget_currentChanged(int)));  // NOLINT
  connect(actionSelect, SIGNAL(triggered()),
          this, SLOT(on_actionSelect_triggered()));
  connect(tabWidget, SIGNAL(tabCloseRequested(int)),
          this, SLOT(on_tabWidget_tabCloseRequest(int)));

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

void MainWindow::openFileNewDialog(ConfigDialog::ConfigDialogType type) {
  // Create the dialog with the configuration it should be in
  ConfigDialog *dialog = new ConfigDialog(type);
  // Connect the dialog to the mainwindow
  connect(dialog, SIGNAL(newDiagramType(BaseNode::DiagramType)),
          this, SLOT(createNewDiagram(BaseNode::DiagramType)));
  connect(dialog, SIGNAL(openDiagramFile(const QString &)),
          this, SLOT(openDiagram(const QString &)));
  dialog->exec();
}

/*! This slot refilters the node actions based on a diagram type. This
    will effectively hide and show menu items and toolbar items.
    @param type The new diagram type
*/
void MainWindow::updateDiagramType(BaseNode::DiagramType type) {
  // Loop through the actions and set their visibility.
  for (int i = 0; i < static_cast<int>(actions.size()); ++i) {
    if (actions.at(i)->getDiagramType() == type) {
      actions.at(i)->setVisible(true);
    } else {
      actions.at(i)->setVisible(false);
    }
  }
}

/*! This slot creates a new Canvas, Document and Tab with the
    given diagram type.
    @param type The new diagram type
*/
void MainWindow::createNewDiagram(BaseNode::DiagramType type) {
  if (type != BaseNode::Nothing) {
    // Create the new document and canvas
    Document *newdoc = new Document;
    documents.push_back(newdoc);
    Canvas* newcanvas = new Canvas;
    canvases.push_back(newcanvas);

    // set the diagram type
    newdoc->setDiagramType(type);

    // set the parent to this so that they get automically deleted
    // when the program shuts down
    // newdoc->setParent(this);
    // newcanvas->setParent(this);

    // Update the canvas and document index on the canvas and document
    newdoc->setCanvasIndex(canvases.size()-1);
    newcanvas->setDocumentIndex(documents.size()-1);

    // add the tab and update the map.
    // Notice that the mapping is inserted before the tab is created. This
    // is so that the mapping is already there when the
    // on_tabWidget_currentChanged slot is called, the mapping is already there.
    // Note that this assumes (which is a valid assumption) that newTabIndex
    // returned by addTab is always equal to the number of tabs.

    // NOTE: Because the tabs can be reordered, tabToCanvasMappings is unused.
    tabToCanvasMappings.insert(
          std::pair<int, int>(tabWidget->count(), canvases.size() - 1));
    int newTabIndex;
    if (type == BaseNode::Class){
        newTabIndex = tabWidget->addTab(newcanvas, "New Class Diagram");
    }
    else if(type == BaseNode::Collaboration){
        newTabIndex = tabWidget->addTab(newcanvas, "New Collaboration Diagram");
    }
    else if(type == BaseNode::UseCase){
        newTabIndex = tabWidget->addTab(newcanvas, "New Use Case Diagram");
    }
    else{
        newTabIndex = tabWidget->addTab(newcanvas, "New Statechart Diagram");
    }

    // Connect the new canvas with the new document.
    connectCanvasWithDocument(canvases.size() - 1, documents.size() - 1);

    // Change to the new tab
    tabWidget->setCurrentIndex(newTabIndex);

    // Update the toolbars
    updateDiagramType(type);
  } else {
    // If the diagram type is nothing and there is no tabs,
    // update the toolbar to reflect it
    if (tabWidget->count() == 0) {
      updateDiagramType(type);
    }
  }
}

/*! This slot opens an existing diagram. It creates a new Canvas, Document
    and tab, then recreates the diagram in the Document.
    @param filename The filename to open.
*/
void MainWindow::openDiagram(const QString &openName) {
  //on_actionOpen_triggered();

  // This function should be similar to the createNewDiagram function, except
  // loads in a diagram after creating the document and canvas. This probably
  // done by calling a slot in the document class with the filename
  // QMessageBox::information(this, "pUML",
  //    "Opening an existing diagram is not yet implemented.\n\n" + filename);

  // read in the diagram type...
  BaseNode::DiagramType diagramType = BaseNode::Class;

  // Create the tab, canvas, and document
  createNewDiagram(diagramType);
  // Update the tab title
  tabWidget->setTabText(tabWidget->currentIndex(), openName);
  documents.at(currentDocument)->openDocument(openName);
}

void MainWindow::documentModifiedChanged(bool modified)
{
  QChar lastchar;
  QString tabtext = tabWidget->tabText(tabWidget->currentIndex());
  lastchar = tabtext.at(tabtext.size()-1);
  if (modified == true) {
    // we need to add a '*' to the end of the tab text
    if (lastchar != '*') {
      tabtext += '*';
    }
  } else {
    // we need to take away any '*' at the end of the tab text
    if (lastchar == '*') {
      tabtext = tabtext.left(tabtext.size()-1);
    }
  }
  tabWidget->setTabText(tabWidget->currentIndex(), tabtext);
}

/*! This slot gets triggered whenever one of the NodeActions are triggered,
  which could be from the toolbar or menu. Those NodeActions hold
  the drawingMode and prototypeID. This slot then puts the canvas and
  document into the right modes and sets the right id's.
  @param drawingMode The drawing mode of the node action. Can be Object,
         Connection, or Nothing
  @param prototypeID The id of the prototype in the NodeFactory. This is
         irrelevant for a drawing mode of Nothing.
*/
void MainWindow::on_NodeAction_triggered(Canvas::DrawingMode drawingMode,
                                         int prototypeID) {
  // QMessageBox::information(this, "setPrototypeID: prototypeID",
  //                          QString::number(prototypeID), QMessageBox::Ok);

  // if (tabWidget->count() != 0 && tabWidget->currentIndex() >= 0
  //     && tabWidget->currentIndex() < tabToCanvasMappings.size()) {
  if (tabWidget->count() != 0 && tabWidget->currentIndex() >= 0) {
    Canvas* currentCanvas;
    // int canvasIndex;

    // Find the current canvas with the map
    // canvasIndex = tabToCanvasMappings[tabWidget->currentIndex()];
    // currentCanvas = canvases.at(canvasIndex);
    currentCanvas = static_cast<Canvas*>(tabWidget->currentWidget());

    // notify the canvas that it should be in object mode
    currentCanvas->setMode(drawingMode);

    // we need to set the prototype id in currently
    // active document, so it knows what to create.
    documents.at(currentCanvas->getDocumentIndex())
            ->setNewObjectID(prototypeID);
  } else {
    qDebug("Node action when there are no canvases created!");
  }
}

/*! This slot updates the currently active canvas's mode to Nothing. It
 *  uses a map of tab indices to canvas indices to find the current canvas.
 *  @todo Try move the mappings into the tabs themselves or into the documents
      to eleminate the need for a map.
 */
void MainWindow::on_actionSelect_triggered() {
  if (tabWidget->count() != 0) {
    // The old way with a dynamic cast
    Canvas* canvas;
    canvas = static_cast<Canvas*>(tabWidget->currentWidget());
    canvas->setMode(Canvas::Nothing);
  }


  /* The new way with the map :) */
  // int canvasIndex;
  // canvasIndex = tabToCanvasMappings[tabWidget->currentIndex()];
  // canvases.at(canvasIndex)->setMode(Canvas::Nothing);
}

/*! Creates a new diagram file.
 *  This slot first uses the openFileNewDialog function open the Open/NEw
    dialog with only new diagram options available. That function connects
    signals from the dialog to the createNewDiagram slot in the MainWindow.
    That slot creates a new diagram, if a new diagram type was chosen.
 */
void MainWindow::on_actionNew_triggered() {
  openFileNewDialog(ConfigDialog::NewOnly);
}

/*! Slot. Executed whenver a tab is closed. Asks to save if the
    document is modifed, and closes the tab.
 */
void MainWindow::on_tabWidget_tabCloseRequest(int index){
  // Check if the document needs saving
  if (documents.at(index)->getModified() == true) {
    QMessageBox::StandardButton choice;
    choice = QMessageBox::question(this, "pUML", "This diagram contains unsaved changes, do you want to save first?",
                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (choice == QMessageBox::Yes) {
      // update the currentdocument to index so that the save function
      // tries to save that document
      int tempindex = currentDocument;
      currentDocument = index;
      on_actionSave_triggered();
      currentDocument = tempindex;
    } else if (choice == QMessageBox::Cancel) {
      return;
    }
  }

  tabWidget->removeTab(index);
  if(tabWidget->count() == 0){
      updateDiagramType(BaseNode::Nothing);
  }
}

/*! Slot. Executed whenever the current tab is changed. Disconnects
    menu and signals from the current document and canvas and connects
    them to the new canvas and document. Also updates the toolbar.
*/
void MainWindow::on_tabWidget_currentChanged(int newIndex) {
  if (newIndex > -1 &&
      newIndex < static_cast<int>(tabToCanvasMappings.size())) {
    // Get the current doc from the current canvas from the current tab
    // Canvas* currentCanvas = canvases.at(tabToCanvasMappings[newIndex]);
    Canvas* currentCanvas = static_cast<Canvas*>(tabWidget->currentWidget());
    Document* currentDoc = documents.at(currentCanvas->getDocumentIndex());
    // and update the toolbar with that document's diagram type.
    updateDiagramType(currentDoc->getDiagramType());

    // disconnect signals that are going to documents
    disconnect(actionSendForwards, SIGNAL(triggered()), 0, 0);
    disconnect(actionSendBackwards, SIGNAL(triggered()), 0, 0);
    disconnect(actionSendToFront, SIGNAL(triggered()), 0, 0);
    disconnect(actionSendToBack, SIGNAL(triggered()), 0, 0);

    // disconnect signals that are coming from the documents
    disconnect(currentDoc, SIGNAL(modifiedChanged(bool)),0,0);

    // connect signals to the current document
    connect(actionSendForwards, SIGNAL(triggered()),
            currentDoc, SLOT(sendSelectedForward()));
    connect(actionSendBackwards, SIGNAL(triggered()),
            currentDoc, SLOT(sendSelectedBackwards()));
    connect(actionSendToFront, SIGNAL(triggered()),
            currentDoc, SLOT(sendSelectedToFront()));
    connect(actionSendToBack, SIGNAL(triggered()),
            currentDoc, SLOT(sendSelectedToBack()));

    // connect signals from the current document
    connect(currentDoc, SIGNAL(modifiedChanged(bool)),
            this, SLOT(documentModifiedChanged(bool)));


  }

  // Note that when the tab changes, the tool automatically goes to select.
  // Maybe we should have some functionality to have the chosen tool be saved from
  // tab to tab?
  actionSelect->trigger();

}

/*! The slot for when the open action is triggered. Opens up a dialog and
    asks for the file name. Then it creates a new tab and opens the document.
    Note that because the diagram is opened in a new tab this function
    doesn't need to check if the diagram needs saving first.
*/
void MainWindow::on_actionOpen_triggered() {
  // First, get a filename.
  QString openName = QFileDialog::getOpenFileName(this, tr("Open Document"),
                                                  "", tr("pUML files (*.puml)"));
  // As long as the user didnt' click cancel...
  if (openName != "") {
    // Use the openDiagram to create the canvas, document and tab and load the file.
    openDiagram(openName);
    updateDiagramType(documents.at(currentDocument)->getDiagramType());
  }
}

/*! The slot for when the save action is triggered. If the currently open
  document is not saved, it triggers the saveas action. If saved successfully
  then the document is marked as saved.
*/
void MainWindow::on_actionSave_triggered() {
  // First, we need a filename. If there is one already, then use that.
  if (documents.at(currentDocument)->hasFilename() == true) {
    documents.at(currentDocument)->saveDocument();
  } else {
    // Otherwise, get a new filename.
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Diagram"),
                                                    "", tr("pUML files (*.puml)"),
                                                    &selectedFilter);
    qDebug(qPrintable(fileName));
    qDebug(qPrintable(selectedFilter));

    // If the user didn't click cancel...
    if (fileName != "") {
      // On linux, the suffix isn't automatically added and we need to
      // manuall add it.
#ifdef Q_OS_LINUX
      if (selectedFilter == "pUML files (*.puml)") {
        fileName += ".puml";
      }
#endif

      // Set the filename for the document (so we know what filename
      // to use later when the user clicks on save again).
      documents.at(currentDocument)->setFilename(fileName);
      // Ask the document to save the document to it's fileName.
      documents.at(currentDocument)->saveDocument();
      // Update the tab's text
      tabWidget->setTabText(tabWidget->currentIndex(), fileName);
    }
  }
}

/*! Slot. Erases the store filename for the current document and
    triggers the save action, so the user is asked to specify a file
    to save to.
*/
void MainWindow::on_actionSave_As_triggered() {
  // FUTURE: This is currently rigged to save only the current document.
  // It will need to iterate over all Document objects and save the nodes
  // vector in each of them.

  // Remove the filename so it appears the document hasn't been given a
  // file name
  documents.at(currentDocument)->setFilename("");
  // Trigger the save to get a new filename
  on_actionSave_triggered();
}

void MainWindow::on_actionPrint_triggered() {
  QPrinter* printer = new QPrinter;
  QPrintDialog printDialog(printer, this);
  if (printDialog.exec() == QDialog::Accepted) {
    //  print ...
  }
  delete printer;
}

void MainWindow::on_actionImport_Export_triggered() {
}

void MainWindow::on_actionExit_triggered() {
  close();
}

void MainWindow::on_actionCopy_triggered() {
}

void MainWindow::on_actionCut_triggered() {
}

void MainWindow::on_actionPaste_triggered() {
}

void MainWindow::on_actionSelect_All_triggered() {
}

void MainWindow::on_actionInverse_Select_triggered() {
}

void MainWindow::on_actionDocument_triggered() {
}

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::about(this, tr("About pUML"),
    tr("<p>The <b>pUML</b> project is the CS383 Software Engeering I Class"
     " final project.</p><p> It was developed by seven awesome students during"
     " their spare time. The development tools is provided by Nokia -- Qt"
     " and Google code repository.</p>"));
}



void MainWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void MainWindow::setSelect()
{
    actionSelect->trigger();
}
