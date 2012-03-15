// Copyright (C) 2011-2012 pUML Group

#include "./UMLnodes_state.h"
#include <algorithm>

StateObject::StateObject() {
  this->length = 50;
  this->height = 50;
}

void StateObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  painter.drawEllipse(position, length / 2, height / 2);

  // edge
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(position, length / 2, height / 2);

  painter.drawText(QRect(position.x() - length / 2, position.y() - height / 2,
                         length, height),
                   Qt::AlignCenter | Qt::AlignHCenter | Qt::TextDontClip,
                   this->name);
}

InitialStateObject::InitialStateObject() {
  this->length = 15;
  this->height = 15;
}


void InitialStateObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::black);
  painter.drawEllipse(position, length / 2, height / 2);
}

FinalStateObject::FinalStateObject() {
  this->length = 30;
  this->height = 30;
}


void FinalStateObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  painter.drawEllipse(position, length / 2, height / 2);

  // edge
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(position, length / 2, height / 2);


  // interior
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::black);
  painter.drawEllipse(position, (length-15) / 2, (height-15) / 2);
}


TransitionConnection::TransitionConnection() {
  extensionLength = -30.0;
}

void TransitionConnection::draw(QPainter &painter) {
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

  pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
  pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

  if (selected == true) {
    QPen selectPen;
    selectPen.setWidth(2);
    selectPen.setColor(Qt::blue);
    painter.setPen(selectPen);
  } else {
    painter.setPen(Qt::black);
  }

  QPainterPath path;
  path.moveTo(pt1);
  calcExtensionPoint();
  path.quadTo(extensionPoint, pt2);
  painter.strokePath(path, painter.pen());
}

void TransitionConnection::calcExtensionPoint()
{
  double a, b, c;
  double x1, x2, y1, y2;
  double x, y;
  int quadrant;

  if (pt1 == pt2) {
    quadrant = 1;
  } else if (pt1.x() == pt2.x()) {
    if (pt2.y() > pt1.y()) {
      quadrant = 2;
    } else {
      quadrant = 4;
    }
  } else if (pt1.y() == pt2.y()) {
    if (pt2.x() < pt1.x()) {
      quadrant = 2;
    } else {
      quadrant = 4;
    }
  } else {
    bool upperhalf, righthalf, lowerhalf, lefthalf;
    upperhalf = (pt2.y() > pt1.y());
    lowerhalf = (pt2.y() < pt1.y());
    righthalf = (pt2.x() > pt1.x());
    lefthalf = (pt2.x() < pt1.x());

    if (upperhalf && righthalf) {
      quadrant = 1;
    }
    if (upperhalf && lefthalf) {
      quadrant = 2;
    }
    if (lowerhalf && righthalf) {
      quadrant = 4;
    }
    if (lowerhalf && lefthalf) {
      quadrant = 3;
    }

  }

  a = abs(pt2.x() - pt1.x());
  b = abs(pt2.y() - pt1.y());

  if (a == 0 && b == 0) {
    extensionPoint = QPoint(pt1.x(), pt1.y()+extensionLength);
  } else {
    if (quadrant == 1 || quadrant == 3) {
      std::swap(a,b);
    }

    c = sqrt(a*a + b*b);
    x1 = a/2.0;
    x2 = extensionLength * (b/c);
    y1 = b/2.0;
    y2 = extensionLength * (a/c);
    x = x1 + x2;
    y = y1 - y2;

    if (quadrant == 1) {
      std::swap(x,y);
    } else if (quadrant == 2) {
      x = -x;
    } else if (quadrant == 3) {
      std::swap(x,y);
      x = -x;
      y = -y;
    } else if (quadrant == 4) {
      y = -y;
    }

    extensionPoint = QPoint(pt1.x() + x,pt1.y() + y);
  }
}
