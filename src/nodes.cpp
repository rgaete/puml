// Copyright (C) 2011-2012 pUML Group

/*!
 * @file nodes.cpp
 *    @brief describes the behavior of the node classes
 */

#include <QMessageBox>
#include <list>
#include "./nodes.h"
#include "./mathfunctions.h"

/**********************************/
/* BaseNode functions *************/
/**********************************/

/*! The BaseNode constructor initializes data
  and sets a unique id.
*/
BaseNode::BaseNode() {
  selected = false;
  cpSelected = false;
  setUpConnectionPoints();
}

void BaseNode::addConnnectionPoint(const QPoint &newpoint) {
  connectionPoints.push_back(newpoint);
}

void BaseNode::addConnectedNode(BaseNode *newObject) {
  connectedObjects.push_back(newObject);
}

void BaseNode::removeConnectedNode(BaseNode *object) {
  connectedObjects.remove(object);
}

QPoint BaseNode::getClosestConnectionPoint(const QPoint &point) {
  double minlength, testlength;
  int minindex;
  // Why not use pow()?
  minlength = sqrt(static_cast<double>(
                   ((point.x() - connectionPoints.at(0).x()) *
                    (point.x() - connectionPoints.at(0).x())) +
                   ((point.y() - connectionPoints.at(0).y()) *
                    (point.y() - connectionPoints.at(0).y()))));
  minindex = 0;

  for (int i = 1; i < static_cast<int>(connectionPoints.size()); i++) {
    testlength = sqrt(static_cast<double>(
                      ((point.x() - connectionPoints.at(i).x()) *
                       (point.x() - connectionPoints.at(i).x())) +
                      ((point.y() - connectionPoints.at(i).y()) *
                       (point.y() - connectionPoints.at(i).y()))));
    if (testlength < minlength) {
      minlength = testlength;
      minindex = i;
    }
  }

  return connectionPoints.at(minindex);
}

std::list<BaseNode*> BaseNode::getConnectedNodes() {
  return std::list<BaseNode*>(connectedObjects);
}

void BaseNode::setUpConnectionPoints() {
  connectionPoints.clear();

  // north
  connectionPoints.push_back(QPoint(position.x(), position.y()-height/2));
  // east
  connectionPoints.push_back(QPoint(position.x()+length/2, position.y()));
  // south
  connectionPoints.push_back(QPoint(position.x(), position.y()+height/2));
  // west
  connectionPoints.push_back(QPoint(position.x()-length/2, position.y()));
}


/**********************************/
/* ObjectNode functions ***********/
/**********************************/

/*! The ObjectNode constructor sets the position variable
  */
ObjectNode::ObjectNode()
  : BaseNode() {
  this->position = position;
}

/*! NOT YET IMPLEMENTED
*/
/*
int ObjectNode::getClosestConnectionPoint(QPoint whereAt) {
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
void ObjectNode::draw(QPainter &painter) {  // NOLINT
  if (selected == true || cpSelected == true) {
    int handleWidth = 5;
    int handleHeight = 5;

    painter.setPen(Qt::NoPen);
    if (cpSelected == true) {
      painter.setBrush(Qt::red);
    } else {
      painter.setBrush(Qt::blue);
    }
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

bool ConnectionNode::hitTest(const QPoint &point) {
  double lineAngle = mathfunctions::computeAngle(pt1, pt2);
  double clickAngle = mathfunctions::computeAngle(pt1, point);
  double lineAngle2 = mathfunctions::computeAngle(pt2, pt1);
  double clickAngle2 = mathfunctions::computeAngle(pt2, point);
  double hypot1 = mathfunctions::calculateHypot(pt1, point);
  double hypot2 = mathfunctions::calculateHypot(pt2, point);

  double clickDistance = fabs(hypot1 * sin(lineAngle - clickAngle));
  double boundary1 = fabs((hypot1 * (cos(lineAngle - clickAngle))));
  double boundary2 = fabs((hypot2 * (cos(lineAngle2 - clickAngle2))));

  if (clickDistance < 15.0 &&
      boundary1 < mathfunctions::calculateHypot(pt1, pt2) &&
      boundary2 < mathfunctions::calculateHypot(pt1, pt2)) {
     return true;
  }
  return false;
}

/*************************************/
/* SquareConnectionNode Functions ****/
/*************************************/
bool SquareConnectionNode::hitTest(const QPoint & point) {
  BaseNode *obj1;
  // BaseNode *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  // it++;
  // obj2 = *(it);

  if (pt1.x() != obj1->getPosition().x()) {  // East or West connection
    if ((fabs(point.x() - ((pt1.x() + pt4.x()) / 2.0)) < 15.0) &&
      ((point.y() < pt1.y() && point.y() > pt4.y()) ||
       (point.y() > pt1.y() && point.y() < pt4.y()))) {
      return true;
    }
    if ((fabs(point.y() - static_cast<double>(pt1.y())) < 15.0) &&
        ((point.x() < pt1.x() && point.x() > pt2.x()) ||
         (point.x() > pt1.x() && point.x() < pt2.x()))) {
      return true;
    }
    if ((fabs(point.y() - static_cast<double>(pt4.y())) < 15.0) &&
        ((point.x() < pt3.x() && point.x() > pt4.x()) ||
         (point.x() > pt3.x() && point.x() < pt4.x()))) { return true;
    }
  } else if (pt1.x() == obj1->getPosition().x()) {  // North or South
                                                    // connection
    if ((fabs(point.y()-((pt1.y() + pt4.y()) / 2.0)) < 15.0) &&
        ((point.x() < pt1.x() && point.x() > pt4.x()) ||
         (point.x() > pt1.x() && point.x() < pt4.x()))) {
      return true;
    }
    if ((fabs(point.x() - static_cast<double>(pt1.x())) < 15.0) &&
        ((point.y() < pt1.y() && point.y() > pt2.y()) ||
         (point.y() > pt1.y() && point.y() < pt2.y()))) {
      return true;
    }
    if ((fabs(point.x() - static_cast<double>(pt4.x())) < 15.0) &&
        ((point.y() < pt3.y() && point.y() > pt4.y()) ||
         (point.y() > pt3.y() && point.y() < pt4.y()))) {
      return true;
    }
  }
  return false;
}
