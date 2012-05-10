#ifndef NODEFACTORYTEST_H
#define NODEFACTORYTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "../nodefactory.h"
#include "../UMLnodes.h"

class NodeFactoryTest : public QObject
{
  Q_OBJECT
  public:
    explicit NodeFactoryTest(QObject *parent = 0);

  signals:

  public slots:

  private slots:
    void initTestCase();
    void testInstance();
    void testRegister();
    void testProduce();
    void cleanupTestCase();
};

#endif // NODEFACTORYTEST_H
