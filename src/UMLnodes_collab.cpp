// Copyright (C) 2011-2012 pUML Group
#include "./UMLnodes_collab.h"
#include <list>

#include "./mathfunctions.h"
/*******************************/
/* StickPersonCollab Functions *******/
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
  painter.drawText(QRect(tempx - length / 2, tempy + height / 2, length, 50),
                   Qt::AlignCenter | Qt::AlignTop | Qt::TextDontClip,
                   this->name);

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
  dialog->setTextValue(name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}

/*******************************/
/* BoxCollab Functions *******/
/*******************************/
BoxCollabObject::BoxCollabObject()
                  :ObjectNode() {
    this->length = 70;
    this->height = 50;
    QPoint pos;
    pos.setX(position.x() + length / 2);
    pos.setY(position.y() + height);
}

void BoxCollabObject::draw(QPainter &painter) {  // NOLINT
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

  painter.drawRect(tempx - 1/2.0 * length,
                     tempy - 1/2.0 * height,
                     length,
                     height);
  // edge
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  // head
    painter.drawRect(tempx - 1/2.0 * length,
                     tempy - 1/2.0 * height,
                     length,
                     height);



  // painter.drawText(tempx-10,tempy+50,this->name);
  painter.drawText(QRect(tempx - length / 2, tempy + height / 2, length, 50),
                   Qt::AlignCenter | Qt::AlignTop | Qt::TextDontClip,
                   this->name);
}

BoxCollabObjectDialog::BoxCollabObjectDialog(QWidget *parent)
                        :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Actor Name:");
  setWindowTitle("Actor Properties");
  setOkButtonText("Ok");
}

QDialog *BoxCollabObject::getDialog() {
  BoxCollabObjectDialog *dialog = new  BoxCollabObjectDialog;
  dialog->setTextValue(name);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}


//square connectors

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

  //These are the initial values i chose to use
  temppoint1.setX(pt2.x());
  temppoint1.setY(pt2.y());
  temppoint2.setX(pt3.x());
  temppoint2.setY(pt3.y());
// these ones were required for a bug fix
  temppoint3.setX(pt1.x());
  temppoint3.setY(pt1.y());
  temppoint4.setX(pt4.x());
  temppoint4.setY(pt4.y());

  // Draws the arrow and computes its direction
  DrawArrow(painter, temppoint1, temppoint2, temppoint3, temppoint4);

  // Draws the text
  painter.drawText(textpos,this->text);
}

QPoint CollabConnection::FindMidPoint(QPoint point1, QPoint point2)
{
    QPoint result;
    int temp1x = point1.x();
    int temp1y = point1.y();
    int temp2x = point2.x();
    int temp2y = point2.y();

    int fx;
    int fy;

    fx = (temp1x + temp2x)/2;
    fy = (temp1y + temp2y)/2;

    result.setX(fx);
    result.setY(fy);

    return result;
}

int CollabConnection::FindDirection(QPoint point1, QPoint point2, QPoint temppoint1, QPoint temppoint2)
{
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


//extra variables
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

    //if point2 is to the right or
    if((fx > 0))// || (fy < 0))
    {
        return -1;
    }
    else if(fx == 0)
    {
        if(gx > 0)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else
        return 1;

}

void CollabConnection::DrawArrow(QPainter &painter, QPoint point1, QPoint point2, QPoint temppoint1,
                                 QPoint temppoint2)
{
    int dir = 1;
    int length = 50;
    int height = 50;

    dir = FindDirection(point1, point2, temppoint1, temppoint2);

    length *= dir;

    int tempx = point1.x()+15;
    int tempy = point1.y()-15;
    int headx = tempx + length/2;
    int heady = tempy;

    // Sets the position of the text
    if(tempx > headx)
    {
        textpos.setX(tempx+5);
        textpos.setY(tempy+5);
    }
    else
    {
        textpos.setX(headx+5);
        textpos.setY(heady+5);
    }

    //sets up the pen
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

  //Draws the body of arrow
    painter.drawLine(tempx,
                     tempy,
                     headx,
                     heady);


    // Bottom arrow
    painter.drawLine(headx,
                     tempy,
                     tempx + length/3,
                     heady + height/6);
    //Top Arrow
    painter.drawLine(headx,
                     tempy,
                     tempx + length/3,
                     heady - height/6);


}

CollabConnectionDialog::CollabConnectionDialog(QWidget *parent)
                        :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Conmnector Name:");
  setWindowTitle("Connector Properties");
  setOkButtonText("Ok");
}

/*! Returns a new CollabConnectionDialog. The dialog is hooked up to
  the setname slot so that it can store any changes made.
*/

QDialog *CollabConnection::getDialog() {
  CollabConnectionDialog *dialog = new CollabConnectionDialog;
  dialog->setTextValue(text);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setName(QString)));
  return dialog;
}
