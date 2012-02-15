/*!
 * @file nodes.cpp
 *      @brief describes the behavior of the node classes
 */

#include "nodes.h"
#include <QMessageBox>

/**********************************/
/* BaseNode functions *************/
/**********************************/

/*! The BaseNode constructor initializes data
    and sets a unique id.
*/
BaseNode::BaseNode()
{
    selected = false;
    setUpConnectionPoints();

}

void BaseNode::addConnnectionPoint(const QPoint &newpoint)
{
    connectionPoints.push_back(newpoint);
}

void BaseNode::addConnectedNode(BaseNode *newObject)
{
    connectedObjects.push_back(newObject);
}

void BaseNode::removeConnectedNode(BaseNode *object)
{
    connectedObjects.remove(object);

}

QPoint BaseNode::getClosestConnectionPoint(const QPoint &point)
{

    double minlength, testlength;
    int minindex;
    minlength = sqrt((double)(point.x() - connectionPoints.at(0).x()) * (point.x() - connectionPoints.at(0).x()) +
                     (point.y() - connectionPoints.at(0).y()) * (point.y() - connectionPoints.at(0).y()));
    minindex = 0;

    for (int i=1; i<(int)connectionPoints.size(); i++) {
        testlength = sqrt((double)(point.x() - connectionPoints.at(i).x()) * (point.x() - connectionPoints.at(i).x()) +
                          (point.y() - connectionPoints.at(i).y()) * (point.y() - connectionPoints.at(i).y()));
        if (testlength < minlength) {
            minlength = testlength;
            minindex = i;
        }
    }

    return connectionPoints.at(minindex);
}

list<BaseNode*> BaseNode::getConnectedNodes()
{
    return list<BaseNode*>(connectedObjects);
}

void BaseNode::setUpConnectionPoints()
{
    connectionPoints.clear();

    //north
    connectionPoints.push_back(QPoint(position.x(), position.y()-height/2));
    //east
    connectionPoints.push_back(QPoint(position.x()+length/2, position.y()));
    //south
    connectionPoints.push_back(QPoint(position.x(), position.y()+height/2));
    //west
    connectionPoints.push_back(QPoint(position.x()-length/2, position.y()));
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

/*! Draws the selection boxes as needed with painter. Assumes
    painter is a valid QPainter.
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

/*! NOT YET IMPLEMENTED */
/*
bool ConnectionNode::hitTest(int x, int y) {
    //functionality for hit testing on lines has
    //not yet been defined.
    return false;
}
*/
