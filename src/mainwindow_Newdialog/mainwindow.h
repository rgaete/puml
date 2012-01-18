#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialognew.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);


private slots:
    void on_actionNew_triggered(bool checked);

    void on_actionOpen_triggered(bool checked);

    void on_actionSave_triggered(bool checked);

    void on_actionSave_As_triggered(bool checked);

    void on_actionPrint_triggered(bool checked);

    void on_actionImport_Export_triggered(bool checked);

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

private:
    Ui::MainWindow *ui;
    dialognew dlg;
    enum diagramType { None=0, UseCase=1, Class=2, Activity=3, Interaction=4, State=5};

};

#endif // MAINWINDOW_H
