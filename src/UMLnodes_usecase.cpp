// Copyright (C) 2011-2012 pUML Group

#include <list>
#include "./UMLnodes_usecase.h"
#include "./mathfunctions.h"
/*******************************/
/* Stickperson Functions *******/
/*******************************/

/*! In the stickperson constructor we set
  the initial length and height and add
  any connection points.
*/
StickPersonObject::StickPersonObject()
                  :ObjectNode() {
  this->length = 50;
  this->height = 70;
  QPoint pos;
  pos.setX(position.x() + length / 2);
  pos.setY(position.y() + height);
  time(&start);
  punchhand = 0;
}


/*! Draws a stickperson on the given painter
  at position. Extends Objectnode.draw().
*/
void StickPersonObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  QPen pen;
  pen.setWidth(2);

  // drawing a stickperson
  int tempx = position.x();
  int tempy = position.y();

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  //! @TODO This needs parenthesis or else needs to be fixed.  // NOLINT
  painter.drawEllipse(tempx - 16 / 2 / 50.0 * length,
                      tempy - (10 + 16) / 70.0 * height,
                      16 / 50.0 * length,
                      16 / 70.0 * height);  // head

  // glove background
  painter.setBrush(Qt::red);
  // right glove
  painter.drawEllipse(
      tempx + 10 / 50.0 * length * punchhand,
      tempy-(300)/70,
      16 / 50.0 * ((length / 2) + (length * (1 - punchhand) / 2)),
      16 / 70.0 * ((height / 2) + (height * (1 - punchhand) / 2)));
  // left glove
  painter.drawEllipse(
      tempx - 20 / 50.0 * length,
      tempy - (300) / 70,
      16 / 50.0 * length / 2,
      16 / 70.0 * height / 2);

  // edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  // neck
  painter.drawLine(tempx, tempy, tempx, tempy - 10 / 70.0 * height);
  // body
  painter.drawLine(tempx, tempy, tempx, tempy + 20 / 70.0 * height);
  // left arm
  painter.drawLine(tempx, tempy, tempx - 10 / 50.0 * length, tempy);
  // right arm
  painter.drawLine(tempx, tempy, tempx + 10 / 50.0 * length * punchhand, tempy);
  // left leg
  painter.drawLine(tempx, tempy+20/70.0*height,
                   tempx - 10 / 50.0 * length,
                   tempy + (20 + 15) / 70.0 * height);
  // right leg
  painter.drawLine(tempx, tempy + 20 / 70.0 * height,
                   tempx + 10 / 50.0 * length,
                   tempy + (20 + 15) / 70.0 * height);
  // head
  painter.drawEllipse(tempx - 16 / 2/50.0 * length,
                      tempy - (10 + 16) / 70.0 * height,
                      16 / 50.0 * length,
                      16 / 70.0 * height);

  //  gloves
  painter.setBrush(Qt::red);

  // right glove
  painter.drawEllipse(
      tempx + 10 / 50.0 * length * punchhand,
      tempy-(300)/70,
      16 / 50.0 * ((length / 2) + (length * (1 - punchhand) / 2)),
      16 / 70.0 * ((height / 2) + (height * (1 - punchhand) / 2)));
  // left glove
  painter.drawEllipse(tempx - 20 / 50.0 * length,
                      tempy - (300) / 70,
                      16 / 50.0 * length / 2,
                      16 / 70.0 * height / 2);

  // painter.drawText(tempx-10,tempy+50,this->name);
  painter.drawText(QRect(tempx - length / 2, tempy + (height-25) / 2, length, 50),
                   Qt::AlignCenter | Qt::AlignTop | Qt::TextDontClip,
                   this->m_name);

  // animation
  time(&end);
  dif = difftime(end, start);
  if (dif >= 0.5) {
    start = end;
    punchhand = 1 - punchhand;
  }
}

/*! The StickDialog constructor initializes the dialog and
  passes parent to QInputDialog.
*/
StickPersonObjectDialog::StickPersonObjectDialog(QWidget *parent)
                        :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Actor Name:");
  setWindowTitle("Actor Properties");
  setOkButtonText("Ok");
}

/*! Returns a new StickDialog. The dialog is hooked up to
  the setname slot so that it can store any changes made.
*/
QDialog *StickPersonObject::getDialog() {
  StickPersonObjectDialog *dialog = new StickPersonObjectDialog;
  dialog->setTextValue(m_name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

/*******************************/
/* Oval Functions **************/
/*******************************/

OvalObject::OvalObject()
           :ObjectNode() {
  this->length = 100;
  this->height = 50;
}

void OvalObject::draw(QPainter &painter) {  // NOLINT
  //The font metrics gets the width of the string and
  //then checks the length of the string against the
  //length of the oval and changes the size accordingly
  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(this->m_name);
  if(temp >= length-20 || temp >= 80){
      temp = temp - (length-20);
      temp = temp + length;
      this->length = temp;
  }
  else{
      this->length = 100;
  }

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);

  painter.drawEllipse(position, length / 2, height / 2);
  // edge
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(position, length / 2, height / 2);
  // painter.drawText(position.x(),position.y(), this->name);
  painter.drawText(QRect(position.x() - length / 2, position.y() - height/2,length, height),
                   Qt::AlignCenter | Qt::AlignHCenter | Qt::TextDontClip,
                   this->m_name);

  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  BaseNode::setUpConnectionPoints();
  ObjectNode::draw(painter);
}

OvalObjectDialog::OvalObjectDialog(QWidget *parent)
                 :QInputDialog(parent) {
  setWindowTitle("Use Case Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("Use Case Name:");
}

QDialog * OvalObject::getDialog() {
  OvalObjectDialog *dialog = new OvalObjectDialog;
  dialog->setTextValue(m_name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

/********************************/
/* Interaction Line Functions ***/
/********************************/


void InteractionConnection::draw(QPainter& painter) {  // NOLINT
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  if (connectedObjects.size() != 2) {
    qDebug() << "InteractionConnection::draw Error: Only " << connectedObjects.size() << " connected objects!";
  } else {
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
    painter.drawLine(pt1, pt2);
  }
}


/********************************/
/* Extends Line Functions *******/
/********************************/
void ExtendsConnection::draw(QPainter &painter) {  // NOLINT
  lineangle = mathfunctions::computeAngle(pt1, pt2);
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::NonCosmeticDefaultPen);

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
  painter.drawLine(pt1, pt2);

  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width("<<extends>>");
  // calculates the midpoint between the objects
  int x = (pt1.x() + pt2.x()) / 2;
  int y = (pt1.y() + pt2.y()) / 2;
  QPoint textPos(x,y);
  int xdist = (pt1.x()-pt2.x())*(pt1.x()-pt2.x());
  int ydist = (pt1.y()-pt2.y())*(pt1.y()-pt2.y());
  if(xdist > ydist && pt1.x() > pt2.x()){
      painter.drawText(textPos.x()-(temp/2),textPos.y()+20,"<<extends>>");
  }
  else if(xdist > ydist && pt1.x() < pt2.x()){
      painter.drawText(textPos.x()-(temp/2),textPos.y()-20,"<<extends>>");
  }
  else{
      painter.drawText(textPos.x()-(temp+5),textPos.y(),"<<extends>>");
  }

  addArrow(painter);
}

void ExtendsConnection::addArrow(QPainter &painter) {  // NOLINT
  const double arrowAngle = 0.75;
  lineangle = mathfunctions::computeAngle(pt1, pt2);
  painter.drawLine(pt2.x(), pt2.y(),
                   pt2.x() + 10 * sin(lineangle - arrowAngle),
                   pt2.y() + 10 * cos(lineangle - arrowAngle));
  painter.drawLine(pt2.x(), pt2.y(),
                   pt2.x() - 10 * sin(lineangle + arrowAngle),
                   pt2.y() - 10 * cos(lineangle + arrowAngle));
}

QPoint ExtendsConnection::calculateTextPosition() {
  double hypot;
  QPoint middle;
  const double textOffset = 35.0;

  if (mathfunctions::toDegrees(lineangle) < 90.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2)/2)-textOffset;
    middle.setX(hypot*cos(-lineangle)+pt1.x());
    middle.setY(hypot*sin(-lineangle)+pt1.y());
  } else if (mathfunctions::toDegrees(lineangle) > 90.0 &&
           mathfunctions::toDegrees(lineangle) <= 180.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2)/2)+textOffset;
    middle.setX(hypot*cos(-lineangle)+pt1.x());
    middle.setY(hypot*sin(-lineangle)+pt1.y());
    lineangle -= PI;
  } else if (mathfunctions::toDegrees(lineangle) > 180.0 &&
           mathfunctions::toDegrees(lineangle) <= 270.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) + textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
    lineangle -= PI;
  } else if (mathfunctions::toDegrees(lineangle) > 270.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) - textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
  }
  return middle;
}

/********************************/
/* Includes Line Functions ******/
/********************************/
void IncludesConnection::draw(QPainter &painter) {  // NOLINT
  lineangle = mathfunctions::computeAngle(pt1, pt2);
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

  pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
  pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::NonCosmeticDefaultPen);

  if (selected == true) {
    QPen selectPen;
    selectPen.setWidth(2);
    selectPen.setColor(Qt::blue);
    painter.setPen(selectPen);
  } else {
    painter.setPen(Qt::black);
  }
  painter.drawLine(pt1, pt2);

  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width("<<includes>>");
  // calculates the midpoint between the objects
  int x = (pt1.x() + pt2.x()) / 2;
  int y = (pt1.y() + pt2.y()) / 2;
  QPoint textPos(x,y);
  int xdist = (pt1.x()-pt2.x())*(pt1.x()-pt2.x());
  int ydist = (pt1.y()-pt2.y())*(pt1.y()-pt2.y());
  if(xdist > ydist && pt1.x() > pt2.x()){
      painter.drawText(textPos.x()-(temp/2),textPos.y()+20,"<<includes>>");
  }
  else if(xdist > ydist && pt1.x() < pt2.x()){
      painter.drawText(textPos.x()-(temp/2),textPos.y()-20,"<<includes>>");
  }
  else{
      painter.drawText(textPos.x()-(temp+5),textPos.y(),"<<includes>>");
  }

  addArrow(painter);
}

void IncludesConnection::addArrow(QPainter &painter) {  // NOLINT
  const double arrowAngle = 0.75;
  lineangle = mathfunctions::computeAngle(pt1, pt2);
  painter.drawLine(pt2.x(), pt2.y(),
                   pt2.x() + 10 * sin(lineangle - arrowAngle),
                   pt2.y() + 10 * cos(lineangle - arrowAngle));
  painter.drawLine(pt2.x(), pt2.y(),
                   pt2.x() - 10 * sin(lineangle + arrowAngle),
                   pt2.y() - 10 * cos(lineangle + arrowAngle));
}

QPoint IncludesConnection::calculateTextPosition() {
  double hypot;
  QPoint middle;
  const double textOffset = 35.0;

  if (mathfunctions::toDegrees(lineangle) < 90.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) - textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
  } else if (mathfunctions::toDegrees(lineangle) > 90.0 &&
             mathfunctions::toDegrees(lineangle) <= 180.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) + textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
    lineangle -= PI;
  } else if (mathfunctions::toDegrees(lineangle) > 180.0 &&
             mathfunctions::toDegrees(lineangle) <= 270.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) + textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
    lineangle -= PI;
  } else if (mathfunctions::toDegrees(lineangle) > 270.0) {
    hypot=(mathfunctions::calculateHypot(pt1, pt2) / 2) - textOffset;
    middle.setX(hypot * cos(-lineangle) + pt1.x());
    middle.setY(hypot * sin(-lineangle) + pt1.y());
  }
  return middle;
}
