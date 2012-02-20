#ifndef PAGES_H
#define PAGES_H

#include <QtGui>

#include <QWidget>
#include <QAction>

class CreateNewPage : public QWidget
{
    Q_OBJECT
public:
    CreateNewPage(QWidget *parent = 0);
    int diagramenum;

    QListWidgetItem *usecaseItem;
    QListWidgetItem *classItem;
    QListWidgetItem *collaborationItem;

signals:

    void return_to_parent();

private slots:
    void ButtonClicked();

};

class CreateOpenPage : public QWidget
{
    Q_OBJECT
public:
    CreateOpenPage(QWidget *parent = 0);

public slots:
    void OpenFileInit();

signals:

    void return_to_parent();

private:
    QAction *Open_Dialog;
};

#endif

