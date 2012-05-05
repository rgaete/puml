// Copyright (C) 2011-2012 pUML Group
#include <QComboBox>
#include <list>

#include "./mathfunctions.h"
#include "./UMLnodes_collab.h"

/*******************************/
/* StickPersonCollab Functions */
/*******************************/

/*! In the StickPersonCollab constructor we set
  the initial length and height and add
  any connection points.
*/
StickPersonCollabObject::StickPersonCollabObject()
                  :ObjectNode() {
  this->length = 50;
  this->height = 70;
  QPoint pos;
  pos.setX(position.x() + length / 2);
  pos.setY(position.y() + height);
  time(&start);
  punchhand = 0;
}


/*! Draws a StickPersonCollab on the given painter
  at position. Extends Objectnode.draw().
*/

void StickPersonCollabObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);

  QPen pen;
  pen.setWidth(2);

  // drawing a StickPersonCollab
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
  painter.drawText(QRect(tempx - length / 2, tempy + (height-25) / 2,
                   length, 50),
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

StickPersonCollabObjectDialog::StickPersonCollabObjectDialog(QWidget *parent)
                              :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Actor Name:");
  setWindowTitle("Actor Properties");
  setOkButtonText("Ok");
}

/*! Returns a new StickDialog. The dialog is hooked up to
  the setname slot so that it can store any changes made.
*/

QDialog *StickPersonCollabObject::getDialog() {
  StickPersonCollabObjectDialog *dialog = new StickPersonCollabObjectDialog;
  dialog->setTextValue(m_name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

/*******************************/
/* BoxCollab Functions   *******/
/*******************************/
BoxCollabObject::BoxCollabObject()
                  :ObjectNode() {
    this->length = 90;
    this->height = 50;
    QPoint pos;
    pos.setX(position.x() + length / 2);
    pos.setY(position.y() + height);
}

void BoxCollabObject::draw(QPainter &painter) {  // NOLINT
  // grabs the length of the string and updates the box
  // to make everything fit properly
  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(this->m_name);

  if (temp >= length-20 || temp >= 70) {
    temp = temp - (length-20);
    temp = temp + length;
    this->length = temp;
  } else {
    this->length = 90;
  }

  QPen pen;
  pen.setWidth(2);

  // drawing a BoxCollab
  int tempx = position.x();
  int tempy = position.y();

  // background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  //! @TODO This needs parenthesis or else needs to be fixed.  // NOLINT

  painter.drawRect(tempx - 1/2.0 * length, tempy - 1/2.0 * height,
                   length, height);
  // edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

    painter.drawRect(tempx - 1/2.0 * length,
                     tempy - 1/2.0 * height,
                     length,
                     height);

  QFont underlineFont;
  underlineFont.setUnderline(true);
  painter.setFont(underlineFont);
  painter.drawText(QRect(tempx - length / 2, tempy - height / 2, length, 50),
                   Qt::AlignCenter | Qt::AlignVCenter,
                   this->m_name);

  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  BaseNode::setUpConnectionPoints();
  ObjectNode::draw(painter);
}

BoxCollabObjectDialog::BoxCollabObjectDialog(QWidget *parent)
                      :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Object Name:");
  setWindowTitle("Object Properties");
  setOkButtonText("Ok");
}

QDialog *BoxCollabObject::getDialog() {
  BoxCollabObjectDialog *dialog = new  BoxCollabObjectDialog;
  dialog->setTextValue(m_name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}


/*******************************/
/* MultiBoxCollab Functions   **/
/*******************************/
MultiBoxCollabObject::MultiBoxCollabObject()
                     :ObjectNode() {
  this->length = 90;
  this->height = 50;
  QPoint pos;
  pos.setX(position.x() + length / 2);
  pos.setY(position.y() + height);
}

void MultiBoxCollabObject::draw(QPainter &painter) {  // NOLINT
  // grabs the length of the string and updates the box
  // to make everything fit properly
  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(this->m_name);

  if (temp >= length-20 || temp >= 70) {
    temp = temp - (length-20);
    temp = temp + length;
    this->length = temp;
  } else {
    this->length = 90;
  }

  QPen pen;
  pen.setWidth(2);

  // drawing a MultiBoxCollab
  int tempx = position.x();
  int tempy = position.y();

  // back box  x,y values
  int backtempx = tempx + 10;
  int backtempy = tempy - 10;

  // back box background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  painter.drawRect(backtempx - 1 / 2.0 * length, backtempy - 1 / 2.0 * height,
                   length, height);

  // back box edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(backtempx - 1 / 2.0 * length, backtempy - 1 / 2.0 * height,
                   length, height);

  // middle box x,y values
  int midtempx = tempx + 5;
  int midtempy = tempy - 5;

  // middle box background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  painter.drawRect(midtempx - 1 / 2.0 * length, midtempy - 1 / 2.0 * height,
                   length, height);

  // middle box edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(midtempx - 1 / 2.0 * length, midtempy - 1 / 2.0 * height,
                   length, height);

  // front box background
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  painter.drawRect(tempx - 1 / 2.0 * length, tempy - 1 / 2.0 * height,
                   length, height);

  // front box edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(tempx - 1 / 2.0 * length, tempy - 1 / 2.0 * height,
                   length, height);

  QFont underlineFont;
  underlineFont.setUnderline(true);
  painter.setFont(underlineFont);
  painter.drawText(QRect(tempx - length / 2, tempy - height / 2, length, 50),
                   Qt::AlignCenter | Qt::AlignVCenter, this->m_name);

  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  BaseNode::setUpConnectionPoints();
  ObjectNode::draw(painter);
}

MultiBoxCollabObjectDialog::MultiBoxCollabObjectDialog(QWidget *parent)
                        :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Object Name:");
  setWindowTitle("Object Properties");
  setOkButtonText("Ok");
}

QDialog *MultiBoxCollabObject::getDialog() {
  MultiBoxCollabObjectDialog *dialog = new  MultiBoxCollabObjectDialog;
  dialog->setTextValue(m_name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}


/***********************************/
/* Square Connectors Collab *******/
/*********************************/

void CollabConnection::draw(QPainter& painter) {  // NOLINT
  QPoint temppoint1;
  QPoint temppoint2;
  QPoint temppoint3;
  QPoint temppoint4;
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

  // These temp values are needed in order to compute the direction of the arrow
  // This is so that the pt values dont get changed
  // These are the initial values i chose to use
  // inner points
  temppoint1.setX(pt2.x());
  temppoint1.setY(pt2.y());
  temppoint2.setX(pt3.x());
  temppoint2.setY(pt3.y());
  // these ones were required for a bug fix
  // outer points
  temppoint3.setX(pt1.x());
  temppoint3.setY(pt1.y());
  temppoint4.setX(pt4.x());
  temppoint4.setY(pt4.y());

  temppoint1.setX(pt2.x());
  if(pt1.y() > pt4.y())
     temppoint1.setY(pt1.y()-40);
  else if(pt1.y() < pt4.y())
      temppoint1.setY(pt1.y()+40);

  // Draws the arrow and computes its direction
  if (pt1.x() == obj1->getPosition().x())
    DrawArrow(painter, temppoint3, temppoint4, temppoint1, temppoint2, 1);
  else if(pt1.x() != obj1->getPosition().x())
    DrawArrow(painter, temppoint1, temppoint2, temppoint3, temppoint4, 0);

  // Draws the text
  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(m_text);

  if (pt1.x() == obj1->getPosition().x()){
    if(pt4.x() >= pt1.x() && pt4.y() > pt1.y())
        painter.drawText(pt1.x()+35,textpos.y(), this->m_text);
    else if (pt4.x() >= pt1.x() && pt4.y() < pt1.y())
        painter.drawText(pt1.x()+35,textpos.y(), this->m_text);
    else if(pt4.x() < pt1.x() && pt4.y() > pt1.y())
        painter.drawText(pt1.x()-temp-35,textpos.y(), this->m_text);
    else if(pt4.x() < pt1.x() && pt4.y() < pt1.y())
        painter.drawText(pt1.x()-temp-35,textpos.y(), this->m_text);
  }
  else if(pt1.x() != obj1->getPosition().x()){
    if(pt4.x() > pt1.x() && pt4.y() >= pt1.y())
        painter.drawText(pt1.x()+50,textpos.y(), this->m_text);
    else if (pt4.x() > pt1.x() && pt4.y() < pt1.y())
        painter.drawText(pt1.x()+50,textpos.y(), this->m_text);
    else if(pt4.x() < pt1.x() && pt4.y() >= pt1.y())
        painter.drawText(pt1.x()-temp-50,textpos.y(), this->m_text);
    else if(pt4.x() < pt1.x() && pt4.y() < pt1.y())
        painter.drawText(pt1.x()-temp-50,textpos.y(), this->m_text);
  }
}


// This function determins the direction of the arrow it returns a 1 to keep the
// arrow facing the same direction or a -1 to make it point backwards
int CollabConnection::FindDirection(QPoint point1, QPoint point2,
                                    QPoint temppoint1, QPoint temppoint2) {
  QPoint result;
  // inner points
  int temp1x = point1.x();
  int temp1y = point1.y();
  int temp2x = point2.x();
  int temp2y = point2.y();

  // Outer points
  int temp3x = temppoint1.x();
  int temp3y = temppoint1.y();
  int temp4x = temppoint2.x();
  int temp4y = temppoint2.y();

  // extra variables
  int fx;
  int fy;
  int gx;
  int gy;
  int absfx;
  int absfy;

  // find differences
  fx = temp1x - temp2x;
  fy = temp1y - temp2y;

  gx = temp3x - temp4x;
  gy = temp3y - temp4y;

  // find absolute values
  absfx = abs(fx);
  absfy = abs(fy);

  // if point2 is to the right or
  if (fx > 0) {  // || (fy < 0))
    return -1;
  } else if (fx == 0) {
    if (gx > 0) {
      return -1;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

// This function is dedicated to the drawing of the arrow
void CollabConnection::DrawArrow(QPainter &painter, QPoint point1,  // NOLINT
                                 QPoint point2, QPoint temppoint1,
                                 QPoint temppoint2, int ud) {
  int dir = 1;  // direction pointing, left or right, initialized to right
  int length = 50;  // length and height variables
  int height = 50;
  int offset = 15;  // offset off of the initial point value on the connection
                    // line
  // finds the direction of the arrow and then sets it to dir
  dir = FindDirection(point1, point2, temppoint1, temppoint2);

  // resets length to either be positive or negative
  length *= dir;

  // computes starting and ending values for the arrow
  int tempx, tempy, headx, heady;
  if(temppoint2.x() >= temppoint1.x() && temppoint2.y() >= temppoint1.y()){
    tempx = temppoint1.x() + offset + 5;
    tempy = temppoint1.y() - offset;
    headx = tempx + length / 2;
    heady = tempy;
  }
  else if (temppoint2.x() >= temppoint1.x() && temppoint2.y() < temppoint1.y()){
    tempx = temppoint1.x() + offset + 5;
    tempy = temppoint1.y() + offset;
    headx = tempx + length / 2;
    heady = tempy;
  }
  else if (temppoint2.x() <= temppoint1.x() && temppoint2.y() >= temppoint1.y()){
    tempx = temppoint1.x() - offset - 5;
    tempy = temppoint1.y() - offset;
    headx = tempx + length / 2;
    heady = tempy;
  }
  else if (temppoint2.x() <= temppoint1.x() && temppoint2.y() < temppoint1.y()){
    tempx = temppoint1.x() - offset - 5;
    tempy = temppoint1.y() + offset;
    headx = tempx + length / 2;
    heady = tempy;
  }


  // Sets the position of the text
  // Initializes the text position relative to the location of the leftmost
  // point of the arrow

  if (tempx > headx) {
    textpos.setX(tempx + 5);
    textpos.setY(tempy + 5);
  } else {
    textpos.setX(headx + 5);
    textpos.setY(heady + 5);
  }

  // sets up the pen
  QPen pen;
  pen.setWidth(2);
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

  int x = temppoint1.x();
  int y = temppoint1.y();

  if(ud == 0){
  // Draws the body of arrow
  painter.drawLine(tempx, tempy, headx, heady);
  // Bottom arrow
  painter.drawLine(headx, tempy, tempx + length / 3, heady + height / 6);
  // Top Arrow
  painter.drawLine(headx, tempy, tempx + length / 3, heady - height / 6);
  }
  else if (ud == 1){
      if(point1.y() > point2.y() && point1.x() <= point2.x()){
          painter.drawLine(x + 20, y ,x + 20, y + 25);
          painter.drawLine(x + 20, y, x + 28, y + 9);
          painter.drawLine(x + 19, y, x + 11, y + 9);
      }
      else if(point1.y() > point2.y() && point1.x() > point2.x()){
          painter.drawLine(x - 20, y ,x - 20, y + 25);
          painter.drawLine(x - 21, y, x - 29, y + 9);
          painter.drawLine(x - 20, y, x - 12, y + 9);
      }
      else if (point1.y() < point2.y() && point1.x() <= point2.x()){
          painter.drawLine(x + 20, y-25,x + 20, y);
          painter.drawLine(x + 20, y, x + 28, y - 9);
          painter.drawLine(x + 19, y, x + 11, y - 9);
      }
      else if (point1.y() < point2.y() && point1.x() > point2.x()){
          painter.drawLine(x - 20, y - 25, x - 20, y);
          painter.drawLine(x - 21, y, x - 29, y - 9);
          painter.drawLine(x - 20, y, x - 12, y - 9);
      }
  }
}

// Dialog for the arrow
CollabConnectionDialog::CollabConnectionDialog(QWidget *parent)
                        :QInputDialog(parent) {
  setWindowTitle("Connector Properties");
  setOkButtonText("Ok");
  setCancelButtonText("Cancel");
  setLabelText("Description:");
}

/*! Returns a new CollabConnectionDialog. The dialog is hooked up to
  the setname slot so that it can store any changes made.
*/

QDialog *CollabConnection::getDialog() {
  CollabConnectionDialog *dialog = new CollabConnectionDialog;
  dialog->setTextValue(m_text);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}


/***********************************/
/* Self Connectors Collab *********/
/*********************************/

void CollabSelfConnection::draw(QPainter& painter) {  // NOLINT
// temporary points so as to not mess up the pt values
  QPoint temppoint1;
  QPoint temppoint2;
  QPoint temppoint3;
  QPoint temppoint4;
  int offset = 15;
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *it;
  obj2 = *it;
  it++;

  pt1 = obj1->returnConnectionPoint(1);
  pt4 = obj2->returnConnectionPoint(2);

  painter.setPen(Qt::black);
  // East connection
  pt2.setY(pt4.y());
  pt2.setX(pt1.x() + offset);
  pt3.setX(pt1.x());
  pt3.setY(pt4.y() + offset);

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

  // These temp values are needed in order to compute the direction of the arrow
  // This is so that the pt values dont get changed
  // These are the initial values i chose to use // inner points
  temppoint1.setX(pt2.x());
  temppoint1.setY(pt2.y());
  temppoint2.setX(pt3.x());
  temppoint2.setY(pt3.y());
  // these ones were required for a bug fix // outer points
  temppoint3.setX(pt1.x());
  temppoint3.setY(pt1.y());
  temppoint4.setX(pt4.x());
  temppoint4.setY(pt4.y());

  // Draws the arrow and computes its direction
  DrawArrow(painter, temppoint2);

  // Draws the text
  painter.drawText(textpos, this->m_text);
}

// This function is dedicated to the drawing of the arrow
void CollabSelfConnection::DrawArrow(QPainter &painter, QPoint point2) {
  int length = -50;  // length and height variables
                     // needs to negative to point the right way
  int height = 50;
  int offset = 10;  // offset off of the initial point value on the connection
                    // line

  // computes starting and ending values for the arrow
  int tempx = point2.x() - length / 2;
  int tempy = point2.y() + offset;
  int headx = tempx + length / 2;
  int heady = tempy;

  // sets up the pen
  QPen pen;
  pen.setWidth(2);
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);

  // Draws the body of arrow
  painter.drawLine(tempx, tempy, headx, heady);

  // Bottom arrow
  painter.drawLine(headx, tempy, tempx + length / 3, heady + height / 6);
  // Top Arrow
  painter.drawLine(headx, tempy, tempx + length / 3, heady - height / 6);

  // Sets the position of the text
  // Initializes the text position right under the arrow
  textpos.setX(headx);
  textpos.setY((heady + height / 6)+ offset);
}

// This function determins the direction of the arrow it returns a 1 to keep
// the arrow facing the same direction or a -1 to make it point backwards

// Dialog for the arrow
CollabSelfConnectionDialog::CollabSelfConnectionDialog(QWidget *parent)
                           :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Connector Name:");
  setWindowTitle("Connector Properties");
  setOkButtonText("Ok");
}

/*! Returns a new CollabSelfConnectionDialog. The dialog is hooked up to
  the setname slot so that it can store any changes made.
*/

QDialog *CollabSelfConnection::getDialog() {
  CollabSelfConnectionDialog *dialog = new CollabSelfConnectionDialog;
  dialog->setTextValue(m_text);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}
