// Copyright (C) 2011-2012 pUML Group

#include <list>

#include "./UMLnodes_class.h"


ClassBoxObject::ClassBoxObject() {
  this->length = 60;
  this->height = 40;
}

void ClassBoxObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  // edge
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(position.x() - length / 2,
                   position.y() - height / 2,
                   length, height);
}

ClassBoxObjectDialog::ClassBoxObjectDialog(QWidget *parent)
                     :QInputDialog(parent) {
  setWindowTitle("ClassBox Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("ClassBox Name:");
}

QDialog * ClassBoxObject::getDialog() {
  ClassBoxObjectDialog *dialog = new ClassBoxObjectDialog;
  dialog->setTextValue(name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

void ClassConnection::draw(QPainter& painter) {  // NOLINT
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *it;
  it++;
  obj2 = *it;

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
