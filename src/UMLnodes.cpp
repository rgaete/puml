#include "nodes.h"
#include "UMLnodes.h"

/*******************************/
/* SimpleLine Functions ********/
/*******************************/

/*! */
/*
SimpleLine::SimpleLine(ObjectNode *point1, ObjectNode *point2)
    :ConnectionNode(point1, point2)
{
    thickness = 2;
}
*/

/*! */
/*
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
*/


/*******************************/
/* Stickperson Functions *******/
/*******************************/

/*! In the stickperson constructor we set
  the initial length and height and add
  any connection points.
*/

StickPerson::StickPerson()
            :ObjectNode() {
    this->length = 50;
    this->height = 70;
    QPoint pos;
    pos.setX(position.x() + length/2);
    pos.setY(position.y() + height);
}


/*! Draws a stickperson on the given painter
    at position.
*/
void StickPerson::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    QPen pen;
    pen.setWidth(2);

    //drawing a stickperson
    int tempx = position.x();
    int tempy = position.y();

    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(tempx-16/2/50.0*length, tempy-(10+16)/70.0*height,16/50.0*length,16/70.0*height); //head

    //edge
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(tempx,tempy,tempx,tempy-10/70.0*height);//neck
    painter.drawLine(tempx,tempy,tempx,tempy+20/70.0*height); //body
    painter.drawLine(tempx,tempy,tempx-10/50.0*length,tempy); //left arm
    painter.drawLine(tempx,tempy,tempx+10/50.0*length,tempy); //right arm
    painter.drawLine(tempx,tempy+20/70.0*height,tempx-10/50.0*length,tempy+(20+15)/70.0*height); //left leg
    painter.drawLine(tempx,tempy+20/70.0*height,tempx+10/50.0*length,tempy+(20+15)/70.0*height); //right leg
    painter.drawEllipse(tempx-16/2/50.0*length, tempy-(10+16)/70.0*height,16/50.0*length,16/70.0*height); //head
}

/*******************************/
/* Oval Functions **************/
/*******************************/

OvalNode::OvalNode()
     :ObjectNode() {
    this->length = 100;
    this->height = 50;
}

void OvalNode::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    painter.drawEllipse(position,length/2,height/2);
    //edge
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(position,length/2,height/2);
}

/*******************************/
/*** ClassRectangle Functions **/
/*******************************/
/*
ClassRectangle::ClassRectangle(QPoint position)
     :ObjectNode(position) {
    this->length = 120;
    this->height = 80;
    this->addConnectionPoint(position);
}

void ClassRectangle::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    painter.save();

    QRect r(0-length/2,0-height/2, length, height-60);
    painter.translate(position);
    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(0-length/2,0-height/2,length,height);
    //edges
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(r);
    painter.drawRect(0-length/2,(0-height/2)+20,length,height-50);
    painter.drawRect(0-length/2,(0-height/2)+50,length,height-50);

    painter.restore();
}
*/

/************************************************/
/********* SquareBoundary Functions *************/
/************************************************/
/*
SquareBoundary::SquareBoundary(QPoint position)
    :ObjectNode(position){
    this->length = 200;
    this->height = 200;
    this->addConnectionPoint(position);
}

void SquareBoundary::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    painter.save();

    QRect r(0-length/2,0-height/2,length,height);
    painter.translate(position);
    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(r);
    //edges
    painter.setPen(Qt::black);
    painter.drawText((0-length/2)+6,(0-height/2)+12,"USE CASE BOUNDARY");
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(r);

    painter.restore();
}
*/


/*******************************/
/* Diamond Functions ***********/
/*******************************/
/*
Diamond::Diamond(QPoint position)
     :ObjectNode(position) {

    this->length = 50;
    this->height = 50;
    this->addConnectionPoint(position);
}

void Diamond::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    painter.save();

    QRect r(0-length/2, 0-height/2, length, height);
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
*/

