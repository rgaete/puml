#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>f
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
    void on_actionSelect_toggled(bool arg1);

    void setPrototypeID(int prototypeID);

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void createWidgets();
    void connectSignalsSlots();
    void registerObjectWithFactory(BaseNode* newPrototype);
    void setCurrentDocument(int index);

private:
    Canvas *canvasWidget;
    //DialogNew *dialogNew;
    vector<QAction*> actions;
    QSignalMapper *signalMapper;
    //! Pointers are used again for polymorphic purposes.
    vector<Document*> documents;
    //! Index pointing to the current document
    int currentDocument;

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
    QAction *actionSelect;
    QAction *actionSelect_All;
    QAction *actionInverse_Select;
    QActionGroup *Shapes_Connectors;
    QAction *actionDocument;
    QAction *actionAbout;
    QAction *actionDelete;
    QAction *actionEdit;

    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuShapes;
    QMenu *menuConnectors;
    QMenu *menuHelp;
    QMenu *menuPopup;

    QToolBar *mainToolBar;
    QStatusBar *statusBar;

};

#endif // MAINWINDOW_H
