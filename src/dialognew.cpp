#include "dialognew.h"

ActorDialog::ActorDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Actor name:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    acceptButton = new QPushButton(tr("Ok"));
    closeButton = new QPushButton(tr("Close"));

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(label);
    inputLayout->addWidget(lineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(acceptButton);
    buttonLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Actor Properties"));

    connect(closeButton, SIGNAL(clicked()),this,SLOT(close()));
    connect(acceptButton, SIGNAL(clicked()),this,SLOT(close()));

}

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
