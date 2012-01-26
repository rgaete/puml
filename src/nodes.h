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
 * This defines the generic drawable object, which includes connectors (arrows and the like)
 * and objects (such as a stick person or a state oval).
 */
class BaseNode {
    public:
        BaseNode();
        //~BaseNode() {}

        int id() {return id_int;}

        void setSelected(bool newState) { selected = newState; }

        virtual void draw(QPainter &painter) =0;
        virtual bool hitTest(int x, int y) =0;
    private:
        int id_int;             //This id is unique for each object in all the
                                //the diagrams that are opened.
    protected:
        bool selected;

};

/*!
 * This abstract base class describes the object nodes.
 * @sa BaseNode
 */
class ObjectNode: public BaseNode {
public:
    ObjectNode(QPoint position);
    //~ObjectNode() {}

    //virtual BaseNode* factory();
    void setPosition(const QPoint &pos) { position = pos; }
    void addConnectionPoint(QPoint point) { connectionPoints.push_back(point); }
    int getClosestConnectionPoint(QPoint whereAt);
    QPoint translateConnectionPoint(int pointIndex);
    QPoint getPosition() { return position; }
    bool hitTest(int x, int y);

protected:
    QRect my_shape;
    QPoint position;
    vector<QPoint> connectionPoints;
    int length;
    int height;

};

/*!
 * This abstract base class describes the connection nodes.
 * Note that even though this class has pointer members,
 * it does not a special copy constructor, assignment operator or
 * destructor for them.
 * @sa BaseNode
 */
class ConnectionNode: public BaseNode {
public:
    ConnectionNode(ObjectNode *point1, ObjectNode *point2);
    ~ConnectionNode();


    //virtual BaseNode* factory();
    bool hitTest(int x, int y);

protected:
    ObjectNode *connectionPoint1;
    ObjectNode *connectionPoint2;

};

/*!
 * This concrete class is the StickPerson node.
 * @sa ObjectNode
 */
class StickPerson: public ObjectNode {
private:
public:
    StickPerson(QPoint position);
    ~StickPerson() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};

/*!
 * This concrete class is the Oval node.
 * @sa ObjectNode
 */
class Oval: public ObjectNode {
private:

public:
    Oval(QPoint position);
    ~Oval() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};

/* !
 *  This concrete class is the ClassRectangle node.
 *  @sa ObjectNode
 */
class ClassRectangle: public ObjectNode {
private:

public:
    ClassRectangle(QPoint position);
    ~ClassRectangle() {}

    void draw(QPainter &painter);
};

class SquareBoundary: public ObjectNode {
private:

public:
    SquareBoundary(QPoint position);
    ~SquareBoundary() {}

    void draw (QPainter &painter);
};

/*!
 * This concrete class is the Diamond node.
 * @sa ObjectNode
 */
class Diamond: public ObjectNode {
private:

public:
    Diamond(QPoint position);
    ~Diamond() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};

/*!
 * This concrete class is the SimpleLine node.
 * @sa ObjectNode
 */
class SimpleLine: public ConnectionNode {
private:
    int thickness;
public:
    SimpleLine(ObjectNode *point1, ObjectNode *point2);
    ~SimpleLine() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};
#endif
