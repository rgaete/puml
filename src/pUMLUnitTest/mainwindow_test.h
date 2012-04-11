#ifndef MAINWINDOW_TEST_H_
#define MAINWINDOW_TEST_H_

#include <QtGui/QApplication>
#include <QtGui/QAction>
#include <QMessageBox>
#include <QObject>
#include <QtTest/QtTest>
#include "../mainwindow.h"

class MainWindowTest : public QObject
{
  Q_OBJECT
  public:
    explicit MainWindowTest(QObject *parent = 0);
    QApplication* app;

  signals:

  public slots:

  private slots:
    void initTestCase();
    void testRegister();
    void cleanupTestCase();
};

#endif // MAINWINDOW_TEST_H_
