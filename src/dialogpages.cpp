#include <QtGui>

#include "dialogpages.h"
#include "dialog.h"


CreateNewPage::CreateNewPage(QWidget *parent)
    : QWidget(parent)
{

    QGroupBox *doctypeGroup = new QGroupBox(tr("Choose Diagram Type"));
//List of widgets
    QListWidget *doctypeList = new QListWidget;

    QListWidgetItem *usecaseItem = new QListWidgetItem(doctypeList);
    usecaseItem->setText(tr("Use Case"));

    QListWidgetItem *classItem = new QListWidgetItem(doctypeList);
    classItem->setText(tr("Class"));

    QListWidgetItem *collaborationItem = new QListWidgetItem(doctypeList);
    collaborationItem->setText(tr("Collaboration"));
//end of list of widgets

    QPushButton *choosedoctypeButton = new QPushButton(tr("Ok"));
    connect(choosedoctypeButton, SIGNAL(clicked()), this, SLOT(close()));

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


CreateOpenPage::CreateOpenPage(QWidget *parent)
    : QWidget(parent)
{

    QPushButton *openButton = new QPushButton(tr("Open File"));
    connect(openButton, SIGNAL(clicked()), this, SLOT(Open_file_init()));

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

void CreateOpenPage::Open_file_init()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this,
         tr("Open Document"),  tr("XML files (*.xml)"));

    // write the loading file function here with the fileName


}

