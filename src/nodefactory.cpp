#include "nodefactory.h"

NodeFactory* NodeFactory::instance = 0;
vector<BaseNode*> NodeFactory::prototypes;

NodeFactory::~NodeFactory()
{
    //delete the pointers
    for (int i=0; i<prototypes.size(); i++) {
        delete prototypes.at(i);
    }
}

int NodeFactory::registerPrototype(BaseNode *newPrototype)
{
   prototypes.push_back(newPrototype);
   return prototypes.size()-1;
}

BaseNode *NodeFactory::produce(int prototype_id)
{
    assert(prototype_id >= 0);
    assert(prototype_id < (int)prototypes.size());
    return prototypes.at(prototype_id)->clone();
}

NodeFactory* NodeFactory::getInstance()
{
    if (instance == 0) {
        instance = new NodeFactory;
    }

    return instance;
}
