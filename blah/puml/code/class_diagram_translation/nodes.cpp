/*!
 * @file nodes.cpp
 *      @brief describes the behavior of the node classes
 */

#include "nodes.h"

/*
bool BaseNode::valid_in(Diagram diagram) {
    cerr << "Invalid call -> BaseNode::valid_in()" << endl;
    return false;
}

int BaseNode::id(string shape) {
    return id_int;
}
*/

/*!
 * Registers the node in the valid_nodes global object.
 */
BaseNode::BaseNode() {
    valid_nodes.register_node(this);
}

ObjectNode::ObjectNode()
           :BaseNode() {
}

StickPerson::StickPerson()
            :ObjectNode() {
}

Oval::Oval()
     :ObjectNode() {
}

void StickPerson::test_msg() {
    cout << "StickPerson::test_msg() --" << endl;
}

void Oval::test_msg() {
    cout << "Oval::test_msg() --" << endl;
}
