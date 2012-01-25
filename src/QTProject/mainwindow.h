#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "canvas.h"


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
    void on_actionSelect_triggered();
    void on_actionSelect_All_triggered();
    void on_actionInverse_Select_triggered();
    void on_actionCircle_toggled(bool arg1);
    void on_actionDiamond_toggled(bool arg1);
    void on_actionRectangle_toggled(bool arg1);
    void on_actionSquare_toggled(bool arg1);
    void on_actionStickMan_toggled(bool arg1);
    void on_actionArrow_toggled(bool arg1);
    void on_actionLine_toggled(bool arg1);
    void on_actionDotted_Line_toggled(bool arg1);
    void on_actionTile_Horizontally_toggled(bool arg1);
    void on_actionTile_Vertically_toggled(bool arg1);
    void on_actionCascade_toggled(bool arg1);
    void on_actionDocument_triggered();
    void on_actionAbout_triggered();

private:
    void setupUI();
    void retranslateUI();

private:
    Canvas *canvasWidget;
    //DialogNew *dialogNew;

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
    QAction *actionCircle;
    QAction *actionDiamond;
    QAction *actionRectangle;
    QAction *actionSquare;
    QAction *actionStickMan;
    QAction *actionArrow;
    QAction *actionLine;
    QAction *actionDotted_Line;
    QAction *actionTile_Horizontally;
    QAction *actionTile_Vertically;
    QAction *actionCascade;
    QAction *actionDocument;

    QAction *actionAbout;
    QAction *actionDelete;
    QAction *actionEdit;
    //QWidget *centralWidget;
    //QScrollBar *verticalScrollBar;
    //QScrollBar *horizontalScrollBar_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuShapes;
    QMenu *menuConnectors;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QMenu *menuPopup;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

};

#endif // MAINWINDOW_H
