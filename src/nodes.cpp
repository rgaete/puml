/*!
 * @file nodes.cpp
 *      @brief describes the behavior of the node classes
 */

#include "nodes.h"

/**********************************/
/* BaseNode functions *************/
/**********************************/

/*! The BaseNode constructor initializes data
    and sets a unique id.
*/
BaseNode::BaseNode()
{
    selected = false;
}

/**********************************/
/* ObjectNode functions ***********/
/**********************************/

/*! The ObjectNode constructor sets the position variable
  */
ObjectNode::ObjectNode()
    : BaseNode()
{
    this->position = position;
}

/*! NOT YET IMPLEMENTED
*/
/*
int ObjectNode::getClosestConnectionPoint(QPoint whereAt)
{
    if (connectionPoints.size() == 0) {
        return -1;
    } else {
        return 0;
    }
}
*/

/*! This is the default implementation of the hitTest function.
    It simply checks if (x,y) is inside the box defined by
    length, length and position. This is a virtual function, so
    it can be reimplemented by children classes as needed.
*/
bool ObjectNode::hitTest(const QPoint &point) {
    if ((point.x() >= (this->position.x()-this->length/2)) &&
        (point.x() <= (this->position.x()+this->length/2))) {
        if ((point.y() >= this->position.y()-this->length/2) &&
            (point.y() <= this->position.y()+this->height/2)) {
            return true;
        }
    }
    return false;
}

/*! Draws the selection boxes as needed
*/
void ObjectNode::draw(QPainter &painter)
{
    if (selected == true) {
        int handleWidth = 5;
        int handleHeight = 5;

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::blue);
        painter.drawRect(position.x()-length/2-handleWidth,
                         position.y()-height/2-handleHeight,
                         handleWidth,
                         handleHeight);
        painter.drawRect(position.x()+length/2,
                         position.y()+height/2,
                         handleWidth,
                         handleHeight);
        painter.drawRect(position.x()+length/2,
                         position.y()-height/2-handleHeight,
                         handleWidth,
                         handleHeight);
        painter.drawRect(position.x()-length/2-handleWidth,
                         position.y()+height/2,
                         handleWidth,
                         handleHeight);
    }
}

/*! NYI
*/
/*
QPoint ObjectNode::translateConnectionPoint(int pointIndex)
{
    if (pointIndex < 0 || pointIndex > (int)connectionPoints.size()-1) {
        //ERROR, index out of bounds
        return QPoint(0,0);
    } else {
        return connectionPoints[pointIndex];
    }
}
*/

/*******************************/
/* ConnectionNode Functions ****/
/*******************************/

/*! */
/*
ConnectionNode::ConnectionNode(ObjectNode *point1, ObjectNode *point2) : BaseNode()
{
    connectionPoint1 = point1;
    connectionPoint2 = point2;
}
*/

/*! */
/*
ConnectionNode::~ConnectionNode()
{
    //Do not delete connectionPoint1 and 2, that is
    //taken care of by the Canvas
}
*/

/*! NOT YET IMPLEMENTED */
/*
bool ConnectionNode::hitTest(int x, int y) {
    //functionality for hit testing on lines has
    //not yet been defined.
    return false;
}
*/
