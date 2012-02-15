/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

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
    connect(choosedoctypeButton, SIGNAL(clicked()), this, SLOT(ConfigDialog::CloseDialog()));



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

