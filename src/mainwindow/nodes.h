/*!
 * @file nodes.h
 *      @brief describes the heirarchy and structure of the node classes.
               This is a copy put into the main Creator project, to be
               updated with the current class diagrams. -Josh 12/4
 */

#ifndef pUML_NODES
#define pUML_NODES

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <QRect>
#include <QPainter>

//#include "utilities.h"
//#include "diagrams.h"

using namespace std;

class BaseNode;

/*!
 * This allows for a dynamic list of nodes.
 * @todo {
 *      Migrate the linked list over to a vector implementation?
 * }
 */
typedef struct linked_nodes {
    BaseNode* node;
    struct linked_nodes* next;
} linked_nodes;

/*!
 * This is a singleton object that lists all possible nodes. The node objects
 * held in this class are not drawn. Instead, they are kept as a toolbar reference.
 * This class has been replaced with a simple vector inside the Canvas class
 */
/*
class AllNodes {
    public:
        AllNodes() {nodes = NULL;}

        void register_node(BaseNode* to_register) {
            debug("> AllNodes::register_node()");
            linked_nodes* cursor;

            if (nodes == NULL) { //Initial registration
                cursor = (linked_nodes*)malloc(sizeof(linked_nodes));
                nodes = cursor;
            } else {
                cursor = nodes;

                while (cursor -> next != NULL) {
                    cursor = cursor -> next;
                }

                cursor -> next = (linked_nodes*)malloc(sizeof(linked_nodes));
                cursor = cursor -> next;
            }

            //cursor now points at last element, where we want to tack on the new node.
            cursor -> node = to_register;
            cursor -> next = NULL;
            debug("< AllNodes::register_node()");
        }
    private:
        linked_nodes* nodes;
};

extern AllNodes valid_nodes;
*/

/*!
 * This defines the generic drawable object, which includes connectors (arrows and the like)
 * and objects (such as a stick person or a state oval).
 */
class BaseNode {
    public:
        //BaseNode();
        //~BaseNode() {}

        int id(string shape) {return -1;}
        string id(int shape_ID) {return "Bad string";}

        virtual void test_msg() {}
        virtual void draw(QPainter &painter) =0;
    private:
        int id_int;
        string id_str;
        //static AllNodes valid_nodes;
};

/*!
 * This abstract base class describes the connection nodes.
 * @sa BaseNode
 */
class ConnectionNode: public BaseNode {
    public:
        //ConnectionNode();
       // ~ConnectionNode();


        //virtual BaseNode* factory();
    private:
};

/*!
 * This abstract base class describes the object nodes.
 * @sa BaseNode
 */
class ObjectNode: public BaseNode {
    public:
        //ObjectNode();
        //~ObjectNode() {}

        //virtual BaseNode* factory();
    private:
        QRect my_shape;
};

/*!
 * This concrete class is the StickPerson node.
 * @sa ObjectNode
 */
class StickPerson: public ObjectNode {
    public:
        StickPerson();
        ~StickPerson() {}

        BaseNode* factory();
        void test_msg();
        void draw(QPainter &painter);
    private:
};

/*!
 * This concrete class is the Oval node.
 * @sa ObjectNode
 */
class Oval: public ObjectNode {
private:
    double centerx;
    double centery;
    double radius;

public:
    Oval();
    ~Oval() {}

    BaseNode* factory();
    void test_msg();
    void draw(QPainter &painter);
};

#endif
