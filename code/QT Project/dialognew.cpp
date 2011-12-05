#include "dialognew.h"

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent)
{
}
void DialogNew::on_OkButton_accepted()
{

}
void DialogNew::on_UseCaseRadioButton_clicked()
{
    //push vector list associated with use case
    diagramType = UseCase;
}
void DialogNew::on_ClassRadioButton_clicked()
{
    diagramType = Class;
}
void DialogNew::on_ActivityRadioButton_clicked()
{
    diagramType = Activity;
}
void DialogNew::on_InteractionRadioButton_clicked()
{
    diagramType = Interaction;
}
void DialogNew::on_StateRadioButton_clicked()
{
    diagramType = State;
}
