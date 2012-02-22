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
    QListWidgetItem *statechartItem;
    QListWidgetItem *collaborationItem;

signals:

    // the return_to_parent function should be changed to send whatever we want back to the parent
    void return_to_parent(int);

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

    void return_to_parent(int);

private:
    QAction *Open_Dialog;
};

#endif

