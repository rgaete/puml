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
  NodeFactory* instance = NodeFactory::getInstance();
  QVERIFY(instance != 0);
}


/*! Tests the registerPrototype function.
*/
void NodeFactoryTest::testRegister() {
  int prototypeID;
  // test register an object
  prototypeID = NodeFactory::getInstance()->registerPrototype(new InheritanceConnection);
  QCOMPARE(prototypeID, 0);

  // test reregistering the same object
  prototypeID = NodeFactory::getInstance()->registerPrototype(new ClassBoxObject);
  QCOMPARE(prototypeID, 1);

  // test registering a null object
  prototypeID = NodeFactory::getInstance()->registerPrototype(0);
  QCOMPARE(prototypeID, 2);
}

void NodeFactoryTest::testProduce()
{
  // Three objects should be registered from the testRegister function
  BaseNode* object, *object2;

  object = NodeFactory::getInstance()->produce(0);
  QCOMPARE(object->metaObject()->className(), "InheritanceConnection");

  object2 = NodeFactory::getInstance()->produce(1);
  QCOMPARE(object2->metaObject()->className(), "ClassBoxObject");

  QVERIFY(object->Id() != object2->Id());

  object = NodeFactory::getInstance()->produce(2);
  QVERIFY(object != 0);

}

/*! Cleans up this unit test
*/
void NodeFactoryTest::cleanupTestCase() {

}
