#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <vector>
#include <nodes.h>
#include "assert.h"

//Singleton

class NodeFactory
{
public:
    ~NodeFactory();

    //call this to register a new prototype. Returns
    //the id of the new prototype (which is an index
    //into the vector
    int registerPrototype(BaseNode* newPrototype);
    //Call this to get a clone of a prototype. Use the
    //id returned by registerPrototype
    BaseNode* produce(int prototype_id);

    static NodeFactory* getInstance();

private:
   NodeFactory() {}                                 // Private so that it can  not be called
   NodeFactory(NodeFactory const &) {}              // copy constructor is private
   NodeFactory& operator=(NodeFactory const&) {}    // assignment operator is private

   vector<BaseNode*> prototypes;
   static NodeFactory* instance;
};

#endif // NODEFACTORY_H
