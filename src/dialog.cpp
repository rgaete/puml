// Copyright (C) 2011-2012 pUML Group

#include <QtGui>

#include <iostream>  // NOLINT

#include "./dialog.h"
#include "./dialogpages.h"

using std::cout;

ConfigDialog::ConfigDialog() {
  contentsWidget = new QListWidget;
  contentsWidget->setViewMode(QListView::IconMode);
  contentsWidget->setIconSize(QSize(96, 84));
  contentsWidget->setMovement(QListView::Static);
  contentsWidget->setMaximumWidth(128);
  contentsWidget->setSpacing(12);

  Newpage = new CreateNewPage;
  Openpage = new CreateOpenPage;

  pagesWidget = new QStackedWidget;
  pagesWidget->addWidget(Newpage);
  pagesWidget->addWidget(Openpage);

  QPushButton *closeButton = new QPushButton(tr("Cancel"));

  createIcons();
  contentsWidget->setCurrentRow(0);

  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  QHBoxLayout *horizontalLayout = new QHBoxLayout;
  horizontalLayout->addWidget(contentsWidget);
  horizontalLayout->addWidget(pagesWidget, 1);

  QHBoxLayout *buttonsLayout = new QHBoxLayout;
  buttonsLayout->addStretch(1);
  buttonsLayout->addWidget(closeButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(horizontalLayout);
  mainLayout->addStretch(1);
  mainLayout->addSpacing(12);
  mainLayout->addLayout(buttonsLayout);
  setLayout(mainLayout);

  setWindowTitle(tr("Intro Program Options"));

  // under construction
  // the connection between the parent and the children
  connect(Newpage,SIGNAL(return_to_parent(int)),  // NOLINT
          this, SLOT(AcceptValue(int)));  // NOLINT
  connect(Openpage,SIGNAL(return_to_parent(int)),  // NOLINT
          this, SLOT(AcceptValue(int)));  // NOLINT
}

// this function is for anything else that should be done prior to closing
// the dialog
void ConfigDialog::CloseDialog() {
  close();
}

// this function is a slot that takes in a value from the children
void ConfigDialog::AcceptValue(int diagramenum) {
  cout << diagramenum <<endl;
  CloseDialog();
}

void ConfigDialog::accepted() {
  emit newDiagramType(ObjectNode::StateChart);
}

void ConfigDialog::createIcons() {
  QListWidgetItem *newbutton = new QListWidgetItem(contentsWidget);
  newbutton->setIcon(QIcon(":/Images/New.png"));
  newbutton->setText(tr("New"));
  newbutton->setTextAlignment(Qt::AlignHCenter);
  newbutton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  QListWidgetItem *openbutton = new QListWidgetItem(contentsWidget);
  openbutton->setIcon(QIcon(":/Images/Open.png"));
  openbutton->setText(tr("Open"));
  openbutton->setTextAlignment(Qt::AlignHCenter);
  openbutton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

  connect(contentsWidget,
          SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
          this, SLOT(changePage(QListWidgetItem*, QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current,
                              QListWidgetItem *previous) {
  if (!current)
    current = previous;

  pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
