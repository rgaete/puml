#ifndef DIALOGNEW_H
#define DIALOGNEW_H
#include <QDialog>
#include <QWidget>
#include "ui_dialognew.h"

class dialognew : public QDialog, Ui::dialognew
{
    Q_OBJECT
    int diagramType;
public:
    dialognew();
    int getDiagramType();
private slots:
     void on_OkButton_accepted();
     void on_UseCaseRadioButton_clicked();
     void on_ClassRadioButton_clicked();
     void on_ActivityRadioButton_clicked();
     void on_InteractionRadioButton_clicked();
     void on_StateRadioButton_clicked();
};

#endif // DIALOGNEW_H


