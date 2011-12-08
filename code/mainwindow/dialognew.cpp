#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <iostream>
#include "dialognew.h"
#include <stdio.h>
using namespace std;

dialognew::dialognew()
{
    setupUi(this);
}
int dialognew::getDiagramType()
{
    return diagramType;
}

void dialognew::on_OkButton_accepted()
{

}
void dialognew::on_UseCaseRadioButton_clicked()
{
    //push vector list associated with use case
    diagramType=1;
}
void dialognew::on_ClassRadioButton_clicked()
{
    diagramType=2;
}
void dialognew::on_ActivityRadioButton_clicked()
{
    diagramType=3;
}
void dialognew::on_InteractionRadioButton_clicked()
{
    diagramType=4;
}
void dialognew::on_StateRadioButton_clicked()
{
    diagramType=5;
}
