// Copyright (C) 2011-2012 pUML Group

#include "./UMLnodes_state.h"

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
  startAngle = 90 * 16;
  spanAngle = 120 * 16;
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
  path.quadTo(QPoint((pt1.x()-pt1.x())/2, pt1.y()-30), pt2);
  painter.drawPath(path);
}
