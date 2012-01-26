#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include <QCloseEvent>

/*! In the MainWindow constructor, we need to create
    all the actions and all the widgets. We call
    setupUI for this.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

/*! Mainwindow deconstructor
*/
MainWindow::~MainWindow()
{
    delete actionNew;
    delete actionOpen;
    delete actionSave;
    delete actionSave_As;
    //... should all the actions be deleted here?
}

/*! Here we are creating all the actions and all the widgets.
*/
void MainWindow::setupUI()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("MainWindow"));
    this->resize(600,500);
    actionNew = new QAction(this);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave_As = new QAction(this);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    actionPrint = new QAction(this);
    actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
    actionImport_Export = new QAction(this);
    actionImport_Export->setObjectName(QString::fromUtf8("actionImport_Export"));
    actionExit = new QAction(this);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    actionCopy = new QAction(this);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    actionCut = new QAction(this);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    actionPaste = new QAction(this);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    actionSelect_All = new QAction(this);
    actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
    actionInverse_Select = new QAction(this);
    actionInverse_Select->setObjectName(QString::fromUtf8("actionInverse_Select"));

    Shapes_Connectors = new QActionGroup(this);
    Shapes_Connectors -> setExclusive(true);

    actionSelect = new QAction(this);
    actionSelect->setIcon(QIcon(":/Images/select.png"));
    actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
    actionSelect->setCheckable(true);
    Shapes_Connectors->addAction(actionSelect);

    actionCircle = new QAction(this);
    actionCircle->setIcon(QIcon(":/Images/oval.png"));
    actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
    actionCircle->setCheckable(true);
    Shapes_Connectors->addAction(actionCircle);

    actionDiamond = new QAction(this);
    actionDiamond->setIcon(QIcon(":/Images/diamond.png"));
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

    actionStickMan = new QAction(this);
    actionStickMan->setIcon(QIcon(":/Images/stickman.png"));
    actionStickMan->setObjectName(QString::fromUtf8("actionStickMan"));
    actionStickMan->setCheckable(true);
    Shapes_Connectors->addAction(actionStickMan);

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


    actionTile_Horizontally = new QAction(this);
    actionTile_Horizontally->setObjectName(QString::fromUtf8("actionTile_Horizontally"));
    actionTile_Horizontally->setCheckable(true);
    actionTile_Vertically = new QAction(this);
    actionTile_Vertically->setObjectName(QString::fromUtf8("actionTile_Vertically"));
    actionTile_Vertically->setCheckable(true);
    actionCascade = new QAction(this);
    actionCascade->setObjectName(QString::fromUtf8("actionCascade"));
    actionCascade->setCheckable(true);
    actionDocument = new QAction(this);
    actionDocument->setObjectName(QString::fromUtf8("actionDocument"));
    actionAbout = new QAction(this);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    //centralWidget = new QWidget(this);
    //centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    //verticalScrollBar = new QScrollBar(centralWidget);
    //verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
    //verticalScrollBar->setGeometry(QRect(650, 0, 20, 401));
    //verticalScrollBar->setOrientation(Qt::Vertical);
    //horizontalScrollBar_2 = new QScrollBar(centralWidget);
    //horizontalScrollBar_2->setObjectName(QString::fromUtf8("horizontalScrollBar_2"));
    //horizontalScrollBar_2->setGeometry(QRect(0, 380, 651, 20));
    //horizontalScrollBar_2->setOrientation(Qt::Horizontal);
    //this->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 673, 21));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    menuTools = new QMenu(menuBar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuShapes = new QMenu(menuTools);
    menuShapes->setObjectName(QString::fromUtf8("menuShapes"));
    menuConnectors = new QMenu(menuTools);
    menuConnectors->setObjectName(QString::fromUtf8("menuConnectors"));
    menuWindow = new QMenu(menuBar);
    menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    this->setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);

    mainToolBar->addAction(actionSelect);
    mainToolBar->addAction(actionCircle);
    mainToolBar->addAction(actionSquare);
    mainToolBar->addAction(actionStickMan);
    mainToolBar->addAction(actionDiamond);
    mainToolBar->addAction(actionRectangle);

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    this->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuTools->menuAction());
    menuBar->addAction(menuWindow->menuAction());
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
    menuShapes->addAction(actionSelect);
    menuShapes->addAction(actionCircle);
    menuShapes->addAction(actionSquare);
    menuShapes->addAction(actionStickMan);
    menuShapes->addAction(actionDiamond);
    menuShapes->addAction(actionRectangle);
    menuConnectors->addAction(actionSelect);
    menuConnectors->addAction(actionArrow);
    menuConnectors->addAction(actionLine);
    menuConnectors->addAction(actionDotted_Line);
    menuWindow->addAction(actionTile_Horizontally);
    menuWindow->addAction(actionTile_Vertically);
    menuWindow->addAction(actionCascade);
    menuHelp->addAction(actionDocument);
    menuHelp->addSeparator();
    menuHelp->addAction(actionAbout);



    canvasWidget = new Canvas(this);
    canvasWidget->setObjectName(QString::fromUtf8("canvasWidget"));
    this->setCentralWidget(canvasWidget);


    retranslateUI();

    menuEdit->setDisabled(true);
    //menuTools->setDisabled(true);
    //menuShapes->setDisabled(true);
    menuWindow->setDisabled(true);

    //manually connect the slots
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_triggered()));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_triggered()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_triggered()));
    connect(actionSave_As, SIGNAL(triggered()), this, SLOT(on_actionSave_As_triggered()));
    connect(actionExit, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()));
    connect(actionPrint, SIGNAL(triggered()), this, SLOT(on_actionPrint_triggered()));
    connect(actionImport_Export, SIGNAL(triggered()), this, SLOT(on_actionImport_Export_triggered()));
    connect(actionSelect, SIGNAL(toggled(bool)), this, SLOT(on_actionSelect_toggled(bool)));
    connect(actionCircle, SIGNAL(toggled(bool)), this, SLOT(on_actionCircle_toggled(bool)));
    connect(actionDiamond, SIGNAL(toggled(bool)), this, SLOT(on_actionDiamond_toggled(bool)));
    connect(actionRectangle, SIGNAL(toggled(bool)), this, SLOT(on_actionRectangle_toggled(bool)));
    connect(actionSquare, SIGNAL(toggled(bool)) ,this, SLOT(on_actionSquare_toggled(bool)));
    connect(actionStickMan, SIGNAL(toggled(bool)) ,this, SLOT(on_actionStickMan_toggled(bool)));
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

void MainWindow::retranslateUI()
{
    this->setWindowTitle(tr("MainWindow"));
    actionNew->setText(tr("New"));
#ifndef QT_NO_TOOLTIP
    actionNew->setToolTip(tr("Create New pUML File"));
#endif // QT_NO_TOOLTIP
    actionOpen->setText(tr("Open"));
#ifndef QT_NO_TOOLTIP
    actionOpen->setToolTip(tr("Open a exsiting pUML file"));
#endif // QT_NO_TOOLTIP
    actionSave->setText(tr("Save"));
#ifndef QT_NO_TOOLTIP
    actionSave->setToolTip(tr("Save current work into file"));
#endif // QT_NO_TOOLTIP
    actionSave_As->setText(tr("Save As.."));
#ifndef QT_NO_TOOLTIP
    actionSave_As->setToolTip(tr("Save current work into another file"));
#endif // QT_NO_TOOLTIP
    actionPrint->setText(tr("Print"));
#ifndef QT_NO_TOOLTIP
    actionPrint->setToolTip(tr("Print the current work"));
#endif // QT_NO_TOOLTIP
    actionImport_Export->setText(tr("Import/Export"));
#ifndef QT_NO_TOOLTIP
    actionImport_Export->setToolTip(tr("Import/Export from/to other UML type file"));
#endif // QT_NO_TOOLTIP
    actionExit->setText(tr("Exit"));
    actionCopy->setText(tr("Copy"));
    actionCut->setText(tr("Cut"));
    actionPaste->setText(tr("Paste"));
    actionSelect->setText(tr("Select"));
    actionSelect_All->setText(tr("Select All"));
    actionInverse_Select->setText(tr("Inverse Select"));
    actionCircle->setText(tr("Circle"));
    actionDiamond->setText(tr("Diamond"));
    actionRectangle->setText(tr("Rectangle"));
    actionSquare->setText(tr("Boundary"));
    actionStickMan->setText(tr("StickMan"));
    actionArrow->setText(tr("Arrow Line"));
    actionLine->setText(tr("Straight Line"));
    actionDotted_Line->setText(tr("Dotted Line"));
    actionTile_Horizontally->setText(tr("Tile Horizontally"));
    actionTile_Vertically->setText(tr("Tile Vertically"));
    actionCascade->setText(tr("Cascade"));
    actionDocument->setText(tr("Help Document"));
    actionAbout->setText(tr("About"));
    menuFile->setTitle(tr("File"));
    menuEdit->setTitle(tr("Edit"));
    menuTools->setTitle(tr("Tools"));
    menuShapes->setTitle(tr("Shapes"));
    menuConnectors->setTitle(tr("Connectors"));
    menuWindow->setTitle(tr("Window"));
    menuHelp->setTitle(tr("Help"));
}

void MainWindow::on_actionNew_triggered()
{
    //dialog of UML types
    //dialogNew = new DialogNew;
    //dialogNew->show();
    QMessageBox::information(this, "HI", "I'm here", QMessageBox::Ok);

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

void MainWindow::on_actionCircle_toggled(bool arg1)
{
    //if this action (menu item or toolbar button)
    //was was toggled on, update the canvas
    if (arg1 == true) {
        canvasWidget->setMode(Canvas::Object);
        canvasWidget->setNewShape(Canvas::ShpOval);
    }
    statusBar->showMessage("Circle");
}

void MainWindow::on_actionDiamond_toggled(bool arg1)
{
    if (arg1 == true) {
        canvasWidget->setMode(Canvas::Object);
        canvasWidget->setNewShape(Canvas::ShpDiamond);
    }
    statusBar->showMessage("Diamond");
}

void MainWindow::on_actionRectangle_toggled(bool arg1)
{
    if (arg1 == true){
        canvasWidget->setMode(Canvas::Object);
        canvasWidget->setNewShape(Canvas::ShpClassRectangle);
    }
    statusBar->showMessage("Class Rectangle");
}

void MainWindow::on_actionSquare_toggled(bool arg1)
{
    if(arg1 == true){
        canvasWidget->setMode(Canvas::Object);
        canvasWidget->setNewShape(Canvas::ShpSquare);
    }
    statusBar->showMessage("Boundary");
}

void MainWindow::on_actionStickMan_toggled(bool arg1)
{
    if (arg1 == true) {
        canvasWidget->setMode(Canvas::Object);
        canvasWidget->setNewShape(Canvas::ShpStickMan);
    }
    statusBar->showMessage("Stickman");
}

void MainWindow::on_actionArrow_toggled(bool arg1)
{

}

void MainWindow::on_actionLine_toggled(bool arg1)
{

}

void MainWindow::on_actionDotted_Line_toggled(bool arg1)
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

void MainWindow::on_actionSelect_toggled(bool arg1)
{
    if (arg1 == true) {
        canvasWidget->setMode(Canvas::Nothing);
    }
    statusBar->showMessage("Selection Mode");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
