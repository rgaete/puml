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

/*!
 * This is a helper method for to_xml that sets an attribute in an XML node.
 *
 * @param doc
 *  This is the document we are creating. Whatever intiates the save will
 *  create this object and will need to make it available in all delegations.
 * @param node
 *  This is the node of the document. For example, when saving the nodes
 *  vector, we create a "Node" element.
 * @param label
 *  This is the name of the attribute we are saving.
 * @param val
 *  This is the value associated with label.
 */
void set_xml_attr(QDomDocument &doc, QDomElement &node,  // NOLINT
                  QString label, QString val) {
  node.setAttribute(label, val);
  /*
  QDomElement el = doc.createElement(label);
  node.appendChild(el);
  QDomText text = doc.createTextNode(val);
  el.appendChild(text);
  */
}

/*!
 * This records the data associated with a node into an XML format.
 *
 * This is used for saving and restoring from save.
 * NOTE: Access to the metaObject *appears* to be contingent on the Q_OBJECT
 * macro being present in THIS class. Thus, if you need to overwrite this
 * method in a derivative class, that derivative class will need the Q_OBJECT
 * macro added.
 *
 * @param doc
 *  This is the document we are creating. Whatever intiates the save will
 *  create this object and will need to make it available in all delegations.
 * @param doc_root
 *  This is the element that will contain this element. The initial design
 *  uses the top level element as the container, hence the name doc_root.
 * @return QDomElement
 *  Based on current implementation, nothing will be done with this return
 *  value. However, in the future, it might be possible to disassociate this
 *  method call from doc.
 */
QDomElement BaseNode::to_xml(QDomDocument &doc,  // NOLINT
                             QDomElement &doc_root) {  // NOLINT
  QDomElement node = doc.createElement("Node");
  doc_root.appendChild(node);

  // Reminder: metaObject depends on the Q_OBJECT macro existing in the class
  // that uses it. Otherwise, the class_name will come out as BaseNode.
  set_xml_attr(doc, node, QString("class_name"),
               this->metaObject()->className());
  set_xml_attr(doc, node, QString("selected"), QString::number(selected, 10));
  set_xml_attr(doc, node, QString("cpSelected"), QString::number(cpSelected));
  set_xml_attr(doc, node, QString("pos_x"), QString::number(position.x()));
  set_xml_attr(doc, node, QString("pos_y"), QString::number(position.y()));
  set_xml_attr(doc, node, QString("length"), QString::number(length));
  set_xml_attr(doc, node, QString("height"), QString::number(height));
  // need to set an xml attribute to get the end points of the connectors
  // need to set an xml attribute to get title (naming) or the

  return node;
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

// gives access to specified connection points
QPoint BaseNode::returnConnectionPoint(int value) {
    return connectionPoints.at(value);
}

int BaseNode::stringLength(const QString &string)
{
    int len=0, max=0, height=0;

    for(int i=0; i < string.length(); i++){
        if(string[i] == '\n' || i == string.length()-1){
            if(max < len)
                max = len;
            len=0;
            height += 1;
        }
        else
            len += 1;
    }

    max = max * 6;
    return max;
}

int BaseNode::stringHeight(const QString &string)
{
    int height=0;

    for(int i=0; i < string.length(); i++){
        if(string[i] == '\n' || i == string.length()-1){
            height += 1;
        }
    }

    return height * 15;
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
