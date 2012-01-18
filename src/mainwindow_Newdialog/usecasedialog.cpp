#include <QtGui>

#include "usecasedialog.h"

UseCaseDialog::UseCaseDialog(QWidget *parent):QDialog(parent)
{
    label = new QLabel(tr("Use Case Name:"));
    lineEdit = new QLineEdit;
    submitButton = new QPushButton(tr("Ok"));
    closeButton = new QPushButton(tr("Cancel"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(label, 0, 0);
    mainLayout->addWidget(lineEdit,1,0,1,10);
    mainLayout->addWidget(submitButton, 2,0);
    mainLayout->addWidget(closeButton, 2,1);
    setLayout(mainLayout);

    setWindowTitle(tr("Use Case Edit"));

    connect(submitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(closeButton, SIGNAL(clicked()),this, SLOT(close()));
}

void UseCaseDialog::okClicked()
{
    QString input = lineEdit->text();

    //Send signal to draw object to update with text in QString
}

