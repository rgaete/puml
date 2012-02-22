#include <QtGui>

#include "dialogpages.h"
#include "dialog.h"
#include <iostream>

using namespace std;

CreateNewPage::CreateNewPage(QWidget *parent)
    : QWidget(parent)
{

    QGroupBox *doctypeGroup = new QGroupBox(tr("Choose Diagram Type"));
//List of widgets
    QListWidget *doctypeList = new QListWidget;

    usecaseItem = new QListWidgetItem(doctypeList);
    usecaseItem->setText(tr("Use Case"));

    classItem = new QListWidgetItem(doctypeList);
    classItem->setText(tr("Class"));

    collaborationItem = new QListWidgetItem(doctypeList);
    collaborationItem->setText(tr("Collaboration"));
//end of list of widgets

    QPushButton *choosedoctypeButton;
    choosedoctypeButton = new QPushButton(tr("Ok"));
    connect(choosedoctypeButton, SIGNAL(clicked()), SLOT(ButtonClicked()));



    QVBoxLayout *updateLayout = new QVBoxLayout;

    QVBoxLayout *doctypeLayout = new QVBoxLayout;
    doctypeLayout->addWidget(doctypeList);
    doctypeGroup->setLayout(doctypeLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(doctypeGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(choosedoctypeButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

}


void CreateNewPage::ButtonClicked()
{
    cout << "here\n";
    if(usecaseItem->isSelected())
    {
        cout <<"usecase\n";
        diagramenum = 1;
        emit return_to_parent();
        close();
    }

    if(classItem->isSelected())
    {
        cout <<"class\n";
        diagramenum = 2;
        emit return_to_parent();
        close();
    }

    if(collaborationItem->isSelected())
    {
        cout <<"collaboration\n";
        diagramenum = 3;
        emit return_to_parent();
        close();

    }

}


CreateOpenPage::CreateOpenPage(QWidget *parent)
    : QWidget(parent)
{

    setParent(parent);

    QPushButton *openButton = new QPushButton(tr("Open File"));
    connect(openButton, SIGNAL(clicked()), this, SLOT(OpenFileInit()));


    QGroupBox *packagesGroup = new QGroupBox(tr("Open File"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(openButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);


}

void CreateOpenPage::OpenFileInit()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,
         tr("Open Document"),  tr("XML files (*.xml)"));

    // write the loading file function here with the fileName


    //
    //parent.close();
}
