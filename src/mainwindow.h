// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QShortcut>
#include <QMainWindow>
#include <QActionGroup>
#include <QHBoxLayout>
#include <QLayout>
#include <QSignalMapper>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGroupBox>
#include <QButtonGroup>
#include <QFile>
#include <QIODevice>

#include <map>
#include <vector>

#include "./UMLnodes.h"
#include "./canvas.h"
#include "./nodefactory.h"
#include "./document.h"
#include "./assert.h"
#include "./nodeaction.h"
#include "./dialog.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  protected:
    void closeEvent(QCloseEvent *event);

  public slots:
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
    void on_actionSelect_All_triggered();
    void on_actionInverse_Select_triggered();
    void on_actionDocument_triggered();
    void on_actionAbout_triggered();
    void on_actionSelect_triggered();
    void on_tabWidget_currentChanged(int newIndex);
    void on_NodeAction_triggered(Canvas::DrawingMode drawingMode,
                                 int prototypeID);
    void setDiagramType(BaseNode::DiagramType type);

  private:
    void createActions();
    void createMenus();
    void createWidgets();
    void connectSignalsSlots();
    void registerObject(BaseNode* newPrototype);
    void connectCanvasWithDocument(int canvasIndex, int documentIndex);


  private:
    // The main document tabs
    QTabWidget *tabWidget;
    // This vector could probably be safely removed.
    std::vector<NodeAction*> actions;
    // The list of open documents
    std::vector<Document*> documents;
    // The canvases in all the tabs
    std::vector<Canvas*> canvases;
    // Index pointing to the current document
    int currentDocument;
    // The status bar
    QStatusBar *statusBar;
    // A 1-to-1 mapping from the tabs to the canvases.
    // There might be a better way to store this data directly in the tabs.
    std::map<int, int> tabToCanvasMappings;

    QToolBar *mainToolBar;
    QLabel *toolbarLabel;

    QActionGroup *toolsActionGroup;
    QActionGroup *connectorsActionGroup;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionImport_Export;
    QAction *actionExit;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionSelect_All;
    QAction *actionInverse_Select;
    QAction *actionDocument;
    QAction *actionAbout;
    QAction *actionDelete;
    QAction *actionEdit;

    QAction *actionSelect;
    QPushButton *buttonSelect;

    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuShapes;
    QMenu *menuConnectors;
    QMenu *menuHelp;
    QMenu *menuPopup;
};

#endif  // SRC_MAINWINDOW_H_
