// Copyright (C) 2011-2012 pUML Group

#include <list>

#include "./UMLnodes_class.h"

void ClassConnection::draw(QPainter& painter) {  // NOLINT
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

  pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
  pt4 = obj2->getClosestConnectionPoint(obj1->getPosition());
  painter.setPen(Qt::black);
  if (pt1.x() == obj1 -> getPosition().x()) {  // North or South connection
    pt2.setY((pt4.y() + pt1.y()) / 2);
    pt2.setX(pt1.x());
    pt3.setX(pt4.x());
    pt3.setY(pt2.y());
  } else if (pt1.x() != obj1->getPosition().x()) {  // East or West connection
    pt2.setY(pt1.y());
    pt2.setX((pt1.x() + pt4.x()) / 2);
    pt3.setX(pt2.x());
    pt3.setY(pt4.y());
  }
  if (selected == true) {
    QPen selectPen;
    selectPen.setWidth(2);
    selectPen.setColor(Qt::blue);
    painter.setPen(selectPen);
    painter.drawLine(pt1, pt2);
  }
  painter.drawLine(pt1, pt2);
  painter.drawLine(pt2, pt3);
  painter.drawLine(pt3, pt4);
}

bool ClassConnection::hitTest(const QPoint &point) {
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

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
         (point.x() > pt3.x() && point.x() < pt4.x()))) {
      return true;
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
