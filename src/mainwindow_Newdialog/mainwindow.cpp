#include <QtGui>
#include "mainwindow.h"
#include "GUI.h"
#include "dialognew.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this, None);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionNew_triggered(bool checked)
{
    //dialog of UML types
    dlg.show();
    ui->setupUi(this, dlg.getDiagramType());
}

void MainWindow::on_actionOpen_triggered(bool checked)
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Document"),  tr("XML files (*.xml)"));

    // write the loading file function here with the fileName
}

void MainWindow::on_actionSave_triggered(bool checked)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       tr("XML files (*.xml)"));

    // write the saving file function here with the fileName
}

void MainWindow::on_actionSave_As_triggered(bool checked)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As File"),
                       tr("XML files (*.xml)"));

    // write the saving as file function here with the fileName
}

void MainWindow::on_actionPrint_triggered(bool checked)
{
    QPrinter* printer = new QPrinter;
    QPrintDialog printDialog(printer,this);
    if (printDialog.exec() == QDialog::Accepted) {
        // print ...
    }
    delete printer;
}

void MainWindow::on_actionImport_Export_triggered(bool checked)
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

void MainWindow::on_actionSelect_triggered()
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
    //change drawing type to circle
}

void MainWindow::on_actionDiamond_toggled(bool arg1)
{

}

void MainWindow::on_actionRectangle_toggled(bool arg1)
{

}

void MainWindow::on_actionStickMan_toggled(bool arg1)
{

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


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
