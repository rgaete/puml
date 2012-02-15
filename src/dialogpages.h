#ifndef PAGES_H
#define PAGES_H

#include <QWidget>

class CreateNewPage : public QWidget
{
public:
    CreateNewPage(QWidget *parent = 0);

};

class CreateOpenPage : public QWidget
{
public:
    CreateOpenPage(QWidget *parent = 0);

public slots:
    void Open_file_init();

private:
    QAction *Open_Dialog;
};

#endif

