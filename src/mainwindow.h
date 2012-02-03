#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <QMessageBox>
#include <QCloseEvent>
#include <QGroupBox>
#include <QButtonGroup>
#include "UMLnodes.h"
#include "canvas.h"
#include "nodefactory.h"
#include "document.h"
#include "assert.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
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
    void on_actionTile_Horizontally_toggled(bool arg1);
    void on_actionTile_Vertically_toggled(bool arg1);
    void on_actionCascade_toggled(bool arg1);
    void on_actionDocument_triggered();
    void on_actionAbout_triggered();
    void on_actionSelect_triggered();

    void setPrototypeID(int prototypeID);

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void createWidgets();
    void connectSignalsSlots();
    void registerObject(BaseNode* newPrototype);
    void setCurrentDocument(int index);

private:
    Canvas *canvasWidget;
    Canvas *test;
    QTabWidget *tabWidget;
    //DialogNew *dialogNew;
    vector<QAction*> actions;
    QSignalMapper *signalMapper;
    //! Pointers are used again for polymorphic purposes.
    vector<Document*> documents;
    //! Index pointing to the current document
    int currentDocument;

    //these frames are for mainToolbar
    QGroupBox *connectorsFrame;
    QVBoxLayout *connectorsFrameLayout;
    QGroupBox *objectsFrame;
    QVBoxLayout *objectsFrameLayout;
    //these button groups are for mainToolbar. They are need so buttons can be exclusively checked.
    QButtonGroup *objectsButtonGroup;
    QButtonGroup *connectorsButtonGroup;
    //A vector to keep track of mainToolbar's buttons (probably could be deleted, no need to access them after they are created)
    vector<QPushButton*> toolbarButtons;
    QToolBar *mainToolBar;
    //! The status bar
    QStatusBar *statusBar;

    //the rightside toolbar, a regular toolbar with a stylesheet targeted towards it (see main.cpp)
    QToolBar *newToolbar;
    //label for newToolbar
    QLabel *toolbarLabel;

    QActionGroup *objectsActionGroup;
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
    QActionGroup *Shapes_Connectors;
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

#endif // MAINWINDOW_H
