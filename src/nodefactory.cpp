#include "nodefactory.h"

//Initialize the static variables
NodeFactory* NodeFactory::instance = 0;          //(Note initially null)
vector<BaseNode*> NodeFactory::prototypes;

/*! The destructor frees up the prototypes
*/
NodeFactory::~NodeFactory()
{
    //delete the pointers
    for (int i=0; i<prototypes.size(); i++) {
        delete prototypes.at(i);
    }
}

/*! Registers a new prototype with the factor and returns the
    unique ID of the prototype.
*/
int NodeFactory::registerPrototype(BaseNode *newPrototype)
{
   prototypes.push_back(newPrototype);
   return prototypes.size()-1;
}

/*! Returns a new copy of the prototype specified by prototype_id.
    Assumes that the id is valid. Functions should use the id
    returned by registoryPrototype.
*/
BaseNode *NodeFactory::produce(int prototype_id)
{
    assert(prototype_id >= 0);
    assert(prototype_id < (int)prototypes.size());
    return prototypes.at(prototype_id)->clone();
}

/*! Returns the one instance of the class. Functions should
    call produce and registerPrototype with this instance.
*/
NodeFactory* NodeFactory::getInstance()
{
    if (instance == 0) {
        instance = new NodeFactory;
    }

    return instance;
}
