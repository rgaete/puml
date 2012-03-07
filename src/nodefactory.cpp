// Copyright (C) 2011-2012 pUML Group

#include "./nodefactory.h"
#include <vector>

// Initialize the static variables
NodeFactory* NodeFactory::instance = 0;      // (Note initially null)
QObject* NodeFactory::m_parent = 0;
std::vector<BaseNode*> NodeFactory::prototypes;

/*! The destructor frees up the prototypes
*/
NodeFactory::~NodeFactory() {
  // delete the pointers
  //for (int i = 0; i < static_cast<int>(prototypes.size()); i++) {
  // delete prototypes.at(i);
  //}
}

/*! Registers a new prototype with the factor and returns the
  unique ID of the prototype. Parent needs to be set before calling this.
  @param newPrototype The prototype to register and clone from.
*/
int NodeFactory::registerPrototype(BaseNode *newPrototype) {
  //assert(m_parent != 0);

  prototypes.push_back(newPrototype);
  newPrototype->setParent(m_parent);
  return prototypes.size()-1;
}

/*! Returns a new copy of the prototype specified by prototype_id.
  Assumes that the id is valid. Functions should use the id
  returned by registoryPrototype. Parent needs to be set beforehand.
  @param prototype_id The id of the prototype to clone. Use the id
         returned from registerPrototype.
*/
BaseNode *NodeFactory::produce(int prototype_id) {
  assert(prototype_id >= 0);
  assert(prototype_id < static_cast<int>(prototypes.size()));
  //assert(m_parent != 0);

  BaseNode* clone;
  clone = prototypes.at(prototype_id)->clone();
  clone->setParent(m_parent);
  return clone;
}

/*! Returns the one instance of the class. Functions should
  call produce and registerPrototype with this instance.
*/
NodeFactory* NodeFactory::getInstance() {
  if (instance == 0) {
    instance = new NodeFactory;
  }

  return instance;
}

/*! Sets the parent property. Every new node cloned will have this
    parent.
    @param parent The parent of all the objects. Can't be null.
*/
void NodeFactory::setParent(QObject *parent)
{
  //assert(parent != 0);
  m_parent = parent;
}
