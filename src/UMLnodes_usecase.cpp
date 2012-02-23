#include "UMLnodes_usecase.h"

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
    pos.setX(position.x() + length/2);
    pos.setY(position.y() + height);
    time(&start);
    punchhand = 0;
}


/*! Draws a stickperson on the given painter
    at position. Extends Objectnode.draw().
*/
void StickPersonObject::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    QPen pen;
    pen.setWidth(2);

    //drawing a stickperson
    int tempx = position.x();
    int tempy = position.y();

    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(tempx-16/2/50.0*length, tempy-(10+16)/70.0*height,16/50.0*length,16/70.0*height); //head

    //glove background
    painter.setBrush(Qt::red);
    painter.drawEllipse(tempx+10/50.0*length*punchhand,tempy-(300)/70,
                        16/50.0*((length/2)+(length*(1 - punchhand)/2)),
                        16/70.0*((height/2)+(height*(1 - punchhand)/2))); //right glove
    painter.drawEllipse(tempx-20/50.0*length,tempy-(300)/70, 16/50.0*length/2,16/70.0*height/2); //left glove

    //edge
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(tempx,tempy,tempx,tempy-10/70.0*height);//neck
    painter.drawLine(tempx,tempy,tempx,tempy+20/70.0*height); //body
    painter.drawLine(tempx,tempy,tempx-10/50.0*length,tempy); //left arm
    painter.drawLine(tempx,tempy,tempx+10/50.0*length*punchhand,tempy); //right arm
    painter.drawLine(tempx,tempy+20/70.0*height,tempx-10/50.0*length,tempy+(20+15)/70.0*height); //left leg
    painter.drawLine(tempx,tempy+20/70.0*height,tempx+10/50.0*length,tempy+(20+15)/70.0*height); //right leg
    painter.drawEllipse(tempx-16/2/50.0*length, tempy-(10+16)/70.0*height,16/50.0*length,16/70.0*height); //head

    // gloves
    painter.setBrush(Qt::red);

    painter.drawEllipse(tempx+10/50.0*length*punchhand,
                        tempy-(300)/70, 16/50.0*((length/2)+(length*(1 - punchhand)/2)),
                        16/70.0*((height/2)+(height*(1 - punchhand)/2))); //right glove
    painter.drawEllipse(tempx-20/50.0*length,tempy-(300)/70, 16/50.0*length/2,16/70.0*height/2); //left glove

    //painter.drawText(tempx-10,tempy+50,this->name);
    painter.drawText(QRect(tempx-length/2, tempy+height/2, length, 50), Qt::AlignCenter | Qt::AlignTop | Qt::TextDontClip, this->name);

    //animation
    time(&end);
    dif = difftime(end, start);
    if(dif >= 0.5)
    {
        start = end;
        punchhand = 1 - punchhand;
    }

}

/*! The StickDialog constructor initializes the dialog and
    passes parent to QInputDialog.
*/
StickPersonObjectDialog::StickPersonObjectDialog(QWidget *parent)
    :QInputDialog(parent)
{
    setCancelButtonText("Cancel");
    setLabelText("Actor Name:");
    setWindowTitle("Actor Properties");
    setOkButtonText("Ok");
}

/*! Returns a new StickDialog. The dialog is hooked up to
    the setname slot so that it can store any changes made.
*/
QDialog *StickPersonObject::getDialog()
{
    StickPersonObjectDialog *dialog = new StickPersonObjectDialog;
    dialog->setTextValue(name);
    connect(dialog,SIGNAL(textValueSelected(QString)),this,SLOT(setName(QString)));
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

void OvalObject::draw(QPainter &painter)
{
    //Always call this ObjectNode's draw function because it
    //draws the selection boxes as needed.
    ObjectNode::draw(painter);

    //background
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);

    painter.drawEllipse(position,length/2,height/2);
    //edge
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(position,length/2,height/2);
    //painter.drawText(position.x(),position.y(), this->name);
    painter.drawText(QRect(position.x()-length/2, position.y()-height/2, length, height),
                     Qt::AlignCenter | Qt::AlignHCenter | Qt::TextDontClip,
                     this->name);
}

OvalObjectDialog::OvalObjectDialog(QWidget *parent)
    :QInputDialog(parent)
{
    setWindowTitle("Use Case Properties");
    setOkButtonText("Ok");
    setCancelButtonText("Cancel");
    setLabelText("Use Case Name:");
}

QDialog * OvalObject::getDialog()
{
    OvalObjectDialog *dialog = new OvalObjectDialog;
    dialog->setTextValue(name);
    connect(dialog,SIGNAL(textValueSelected(QString)),this,SLOT(setName(QString)));
    return dialog;
}

/********************************/
/* Interaction Line Functions ***/
/********************************/


void InteractionConnection::draw(QPainter& painter)
{

    QPoint pt1, pt2;
    BaseNode *obj1, *obj2;
    list<BaseNode*>::iterator it = connectedObjects.begin();
    obj1 = *(it);
    it++;
    obj2 = *(it);

    pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
    pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

    painter.setPen(Qt::black);
    painter.drawLine(pt1, pt2);

}

/********************************/
/* Extends Line Functions *******/
/********************************/
void ExtendsConnection::draw(QPainter &painter)
{
    QPoint pt1, pt2;
    BaseNode *obj1, *obj2;
    list<BaseNode*>::iterator it = connectedObjects.begin();
    obj1 = *(it);
    it++;
    obj2 = *(it);

    pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
    pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

    painter.setPen(Qt::black);
    painter.drawLine(pt1, pt2);

    //draw the text
    painter.save();
    QPoint middle = QPoint((pt1.x()+pt2.x())/2, (pt1.y()+pt2.y())/2);
    painter.translate(middle);
    //double angle = acos((pt1.y() - pt2.y())/(hypot(pt1.x()-pt2.x(),pt1.y()-pt2.y())));
    //painter.rotate(angle*(180.0/(atan(1)*4)));
    painter.drawText(0,0,"<<extends>>");
    painter.restore();
}

/********************************/
/* Includes Line Functions ******/
/********************************/
void IncludesConnection::draw(QPainter &painter)
{
    QPoint pt1, pt2;
    BaseNode *obj1, *obj2;
    list<BaseNode*>::iterator it = connectedObjects.begin();
    obj1 = *(it);
    it++;
    obj2 = *(it);

    pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
    pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

    painter.setPen(Qt::black);
    painter.drawLine(pt1, pt2);

    //draw the text
    painter.save();
    QPoint middle = QPoint((pt1.x()+pt2.x())/2, (pt1.y()+pt2.y())/2);
    painter.translate(middle);
    //double angle = acos((pt1.y() - pt2.y())/(hypot(pt1.x()-pt2.x(),pt1.y()-pt2.y())));
    //painter.rotate(angle*(180.0/(atan(1)*4)));
    painter.drawText(0,0,"<<includes>>");
    painter.restore();
}
