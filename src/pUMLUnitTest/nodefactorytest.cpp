#include "nodefactorytest.h"

NodeFactoryTest::NodeFactoryTest(QObject *parent) :
    QObject(parent)
{
}

/*! Initializes this unit test
*/
void NodeFactoryTest::initTestCase() {

}

/*! Tests the registerPrototype function.
*/
void NodeFactoryTest::testRegister() {

    QCOMPARE(1,1);
}

/*! Cleans up this unit test
*/
void NodeFactoryTest::cleanupTestCase() {

}
