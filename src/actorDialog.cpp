#include <QtGui>
#include <actorDialog.h>

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

}
