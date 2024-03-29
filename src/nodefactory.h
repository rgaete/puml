// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_NODEFACTORY_H_
#define SRC_NODEFACTORY_H_

#include <vector>
#include "./nodes.h"
#include "./assert.h"

// Singleton
class NodeFactory {
  public:
    ~NodeFactory();

    static int registerPrototype(BaseNode* newPrototype);
    static BaseNode* produce(int prototype_id);
    static BaseNode* produceFromClassName(QString name);
    static NodeFactory* getInstance();

  private:
    // Constructor is private so the class cannot be instantiated.
    NodeFactory() {}
    // Copy Constructor is private so the class cannot be coppied.
    explicit NodeFactory(NodeFactory const &) {}
    // Assignment operated is private so the class cannot be assigned.
    NodeFactory& operator=(NodeFactory const&) { return *this; }

    // The vector of prototypes. This is static so the lifetime is
    // the entire execution time of the program.
    static std::vector<BaseNode*> prototypes;
    // The single instance of the class. Static so the lifetime is
    // the entire lifetime of the program.
    static NodeFactory* instance;
};

#endif  // SRC_NODEFACTORY_H_
