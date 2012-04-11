// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QAction>
#include <QActionGroup>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIODevice>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>
#include <QShortcut>
#include <QSignalMapper>
#include <QStatusBar>
#include <QString>
#include <QToolBar>
#include <QXmlStreamReader>

#include <map>
#include <vector>
#include <algorithm>

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
    void updateDiagramType(BaseNode::DiagramType type);
    void createNewDiagram(BaseNode::DiagramType type);
    void openDiagram(const QString &filename);

  private:
    void createActions();
    void createMenus();
    void createWidgets();
    void connectSignalsSlots();
    void openFileNewDialog(ConfigDialog::ConfigDialogType type);
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
    // A 1-to-1 mapping from the tab indexes to the canvas indexes.
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
    QAction *actionSendForwards;
    QAction *actionSendBackwards;
    QAction *actionSendToBack;
    QAction *actionSendToFront;

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
    QString openName;
};

#endif  // SRC_MAINWINDOW_H_
