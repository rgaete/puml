// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DIALOGPAGES_H_
#define SRC_DIALOGPAGES_H_

#include <QtGui>

#include <QWidget>
#include <QAction>

class CreateNewPage : public QWidget {
  Q_OBJECT

  public:
    explicit CreateNewPage(QWidget *parent = 0);
    int diagram_enum;

    QListWidgetItem *usecaseItem;
    QListWidgetItem *classItem;
    QListWidgetItem *statechartItem;
    QListWidgetItem *collaborationItem;

  signals:
    // the return_to_parent function should be changed to send whatever we
    // want back to the parent
    void return_to_parent(int diagram_enum);

  private slots:
    void ButtonClicked();
};

class CreateOpenPage : public QWidget {
  Q_OBJECT

  public:
    explicit CreateOpenPage(QWidget *parent = 0);

  public slots:
    void OpenFileInit();

  signals:
    void return_to_parent(int diagram_enum);

  private:
    QAction *Open_Dialog;
};

#endif  // SRC_DIALOGPAGES_H_
