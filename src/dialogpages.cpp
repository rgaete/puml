// Copyright (C) 2011-2012 pUML Group

#include <QtGui>

#include "./dialogpages.h"
#include "./dialog.h"
// #include <iostream>

// using namespace std;

CreateNewPage::CreateNewPage(QWidget *parent)
              :QWidget(parent) {
  QGroupBox *doctypeGroup = new QGroupBox(tr("Choose Diagram Type"));
// List of widgets
  // There should be one for each diagram type
  QListWidget *doctypeList = new QListWidget;

  usecaseItem = new QListWidgetItem(doctypeList);
  usecaseItem->setText(tr("Use Case"));

  classItem = new QListWidgetItem(doctypeList);
  classItem->setText(tr("Class"));

  statechartItem = new QListWidgetItem(doctypeList);
  statechartItem->setText(tr("State Chart"));

  collaborationItem = new QListWidgetItem(doctypeList);
  collaborationItem->setText(tr("Collaboration"));
// end of list of widgets

  QPushButton *choosedoctypeButton;
  choosedoctypeButton = new QPushButton(tr("Ok"));
  connect(choosedoctypeButton, SIGNAL(clicked()), SLOT(ButtonClicked()));

// default layout stuff
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


// What the program does when the "OK" button is clicked
void CreateNewPage::ButtonClicked() {
  fprintf(stderr, "here\n");
  if (usecaseItem->isSelected()) {
    fprintf(stderr, "usecase\n");
    diagram_enum = 1;
    emit return_to_parent(diagram_enum);
    close();
  }

  if (classItem->isSelected()) {
    fprintf(stderr, "class\n");
    diagram_enum = 2;
    emit return_to_parent(diagram_enum);
    close();
  }

  if (statechartItem->isSelected()) {
    fprintf(stderr, "state chart\n");
    diagram_enum = 3;
    emit return_to_parent(diagram_enum);
    close();
  }

  if (collaborationItem->isSelected()) {
    fprintf(stderr, "collaboration\n");
    diagram_enum = 4;
    emit return_to_parent(diagram_enum);
    close();
  }
}


CreateOpenPage::CreateOpenPage(QWidget *parent)
               :QWidget(parent) {
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

void CreateOpenPage::OpenFileInit() {
  QString fileName;

  fileName = QFileDialog::getOpenFileName(this,
     tr("Open Document"),  tr("XML files (*.xml)"));

  // write the loading file function here with the fileName

  // returning to parent
  emit return_to_parent(0);
}
