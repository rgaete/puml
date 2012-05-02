#include "nodefactorytest.h"

NodeFactoryTest::NodeFactoryTest(QObject *parent)
                :QObject(parent) {
}

/*! Initializes this unit test
*/
void NodeFactoryTest::initTestCase() {

}

void NodeFactoryTest::testInstance()
{
  //NodeFactory* instance = new
}


/*! Tests the registerPrototype function.
*/
void NodeFactoryTest::testRegister() {
  int prototypeID;
  // test register an object
  prototypeID = NodeFactory::getInstance()->registerPrototype(new OvalObject);
  QCOMPARE(prototypeID, 0);

  // test reregistering the same object
  prototypeID = NodeFactory::getInstance()->registerPrototype(new OvalObject);
  QCOMPARE(prototypeID, 1);

  // test registering a null object
  prototypeID = NodeFactory::getInstance()->registerPrototype(0);
  QCOMPARE(prototypeID, 2);
}

void NodeFactoryTest::testProduce()
{

}

/*! Cleans up this unit test
*/
void NodeFactoryTest::cleanupTestCase() {

}
