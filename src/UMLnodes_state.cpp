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

StateObjectDialog::StateObjectDialog(QWidget *parent)
                  :QInputDialog(parent) {
  setWindowTitle("State Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("State Name:");
}

QDialog * StateObject::getDialog() {
  StateObjectDialog *dialog = new StateObjectDialog;
  dialog->setTextValue(name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

InitialStateObjectDialog::InitialStateObjectDialog(QWidget *parent)
                         :QInputDialog(parent) {
  setWindowTitle("State Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("State Name:");
}

QDialog * InitialStateObject::getDialog() {
  InitialStateObjectDialog *dialog = new InitialStateObjectDialog;
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

FinalStateObjectDialog::FinalStateObjectDialog(QWidget *parent)
                 :QInputDialog(parent) {
  setWindowTitle("State Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("State Name:");
}

QDialog * FinalStateObject::getDialog() {
  FinalStateObjectDialog *dialog = new FinalStateObjectDialog;
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}
