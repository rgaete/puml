#include <QtGui>

#include "dialog.h"
#include "dialogpages.h"

ConfigDialog::ConfigDialog()
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new CreateNewPage);
    pagesWidget->addWidget(new CreateOpenPage);

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

    //under construction
    //connect(pagesWidget, SIGNAL(return_to_parent()), this, SLOT(CloseDialog()));

    connect(pagesWidget,SIGNAL(widgetRemoved(int)), this, SLOT(CloseDialog()));
}

void ConfigDialog::CloseDialog()
{
    close();
}

void ConfigDialog::accepted()
{
    //emit newDiagramType(BaseNode::UseCase);
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *newbutton = new QListWidgetItem(contentsWidget);
    newbutton->setIcon(QIcon(":/Images/stickman.png"));
    newbutton->setText(tr("New"));
    newbutton->setTextAlignment(Qt::AlignHCenter);
    newbutton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *openbutton = new QListWidgetItem(contentsWidget);
    openbutton->setIcon(QIcon(":/Images/diamond.png"));
    openbutton->setText(tr("Open"));
    openbutton->setTextAlignment(Qt::AlignHCenter);
    openbutton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}


