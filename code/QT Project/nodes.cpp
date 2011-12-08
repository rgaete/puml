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
/*BaseNode::BaseNode() {
    valid_nodes.register_node(this);
}*/

/* ObjectNode functions ***********/

ObjectNode::ObjectNode(QPoint pos) : BaseNode()
{
    position = pos;
}

int ObjectNode::getClosestConnectionPoint(QPoint whereAt)
{
    if (connectionPoints.size() == 0) {
        return -1;
    } else {
        return 0;
    }
}

QPoint ObjectNode::translateConnectionPoint(int pointIndex)
{
    if (pointIndex < 0 || pointIndex > (int)connectionPoints.size()-1) {
        //ERROR, index out of bounds
        return QPoint(0,0);
    } else {
        return connectionPoints[pointIndex];
    }
}


/* ConnectionNode Functions ****/

ConnectionNode::ConnectionNode(ObjectNode *point1, ObjectNode *point2) : BaseNode()
{
    connectionPoint1 = point1;
    connectionPoint2 = point2;
}

ConnectionNode::~ConnectionNode()
{
    //Do not delete connectionPoint1 and 2, that is
    //taken care of by the Canvas
}

/* SimpleLine Functions ********/

SimpleLine::SimpleLine(ObjectNode *point1, ObjectNode *point2)
    :ConnectionNode(point1, point2)
{
    thickness = 2;
}

void SimpleLine::draw(QPainter &painter)
{
    //We want to draw a line from connectionPoint1's
    //connection point to connectionPoint2's
    //connection point.

    int point1index, point2index;
    point1index = connectionPoint1->getClosestConnectionPoint(connectionPoint2->getPosition());
    point2index = connectionPoint2->getClosestConnectionPoint(connectionPoint1->getPosition());

    QPoint point1, point2;
    point1 = connectionPoint1->translateConnectionPoint(point1index);
    point2 = connectionPoint2->translateConnectionPoint(point2index);

    QPen pen;
    int lineThickness = 1;
    QColor lineColor = QColor(Qt::black);
    pen.setWidth(lineThickness);
    pen.setColor(lineColor);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    painter.drawLine(point1,point2);

}



/* Stickperson Functions *******/

/*StickPerson::StickPerson()
            :ObjectNode() {
}*/

void StickPerson::draw(QPainter &painter)
{
    //drawing a stickperson

}

/* Oval Functions **************/

Oval::Oval(QPoint pos)
     :ObjectNode(pos) {
    this->radius = 50;
    //Adding a connection point at the center
    //is a cheap shortcut. Needs to be updated.
    this->addConnectionPoint(pos);
}

void Oval::draw(QPainter &painter)
{
    //drawing an oval
    int tempx = position.x();
    int tempy = position.y();
    int tempr = radius;

    QPoint point(tempx, tempy);
    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(point,tempr, tempr);
    //edge
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(point,tempr, tempr);
}

/* Diamond Functions ***********/
Diamond::Diamond(QPoint pos)
     :ObjectNode(pos) {
    this->width = 50;
    this->height = 50;
    this->addConnectionPoint(pos);
}

void Diamond::draw(QPainter &painter)
{
    painter.save();

    QRect r(0-width/2, 0-height/2, width, height);
    painter.translate(position);
    painter.rotate(45);
    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(r);
    //edge
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(r);
    painter.rotate(-45);

    painter.restore();

}


