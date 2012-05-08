// Copyright (C) 2011-2012 pUML Group

#include "./UMLnodes_state.h"
#include <algorithm>
#include "./mathfunctions.h"
#include <QVBoxLayout>
#include <QPushButton>

StateObject::StateObject() {
  this->length = 80;
  this->height = 80;
  this->m_finalstate = false;
}

void StateObject::draw(QPainter &painter) {  // NOLINT
    //The font metrics gets the width of the string and
    //then checks the length of the string against the
    //length of the oval and changes the size accordingly
    QFontMetrics fm = painter.fontMetrics();
    int temp = fm.width(this->m_name);
    int alength, aheight;

    alength = stringLength(this->m_attributes);
    aheight = stringHeight(this->m_attributes);

    if(temp >= length-40 || temp >= 70 || alength+10 >= length -40 || alength >= 70){
        if( temp > alength){
            temp = temp - (length-30);
            temp = temp + length;
            this->length = temp;
        }
        else{
            alength = alength - (length-30);
            alength = alength + length;
            this->length = alength;
        }
    }
    else{
        this->length = 80;
    }
    if(aheight >= height-55){
        aheight = aheight + 45;
        this->height = aheight;
    }
    else{
        this->height = 80;
    }

  // QPainter::Antialiasing;

  if(m_finalstate == true){
        // background
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::white);
        painter.drawRoundedRect(position.x()-length/2,position.y()-height/2,length,height,12,12);

        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);
        painter.drawRoundedRect(position.x()-length/2,position.y()-height/2,length,height,12,12);
  }
  else{
      painter.setPen(Qt::NoPen);
      painter.setBrush(Qt::white);
      painter.drawRoundedRect(position.x()-length/2+5,position.y()-height/2+5,length-10,height-10,12,12);
  }

  // edge
  painter.setPen(Qt::black);
  painter.setBrush(Qt::NoBrush);
  painter.drawRoundedRect(position.x()-length/2+5,position.y()-height/2+5,length-10,height-10,12,12);
  painter.drawLine(position.x()-length/2+5, position.y()-height/2 + 35,
                   position.x()+length/2-5, position.y()-height/2 + 35);

  QFont boldFont;
  boldFont.setBold(true);
  painter.setFont(boldFont);
  painter.drawText(QRect(position.x() - length / 2, position.y() - height + 20,
                         length, height),
                   Qt::AlignCenter | Qt::AlignHCenter | Qt::TextDontClip,
                   this->m_name);

   const QFont normalFont;
   painter.setFont(normalFont);

   QRect attributesSection(position.x() - (length / 2) + 12,
                           position.y() - (height / 2) + 40,
                           length, height);
   painter.drawText(attributesSection, m_attributes);


  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  BaseNode::setUpConnectionPoints();
  ObjectNode::draw(painter);
}

void StateObject::setFinal(bool state)
{
    m_finalstate = state;
}

StateObjectDialog::StateObjectDialog(QWidget *parent)
                 :QDialog(parent) {

    okButton = new QPushButton(tr("Ok"), this);

    NameLabel = new QLabel(tr("State Name:"), this);
    AttributesLabel = new QLabel(tr("Attributes:"), this);

    NameLineEdit = new QLineEdit(this);
    AttributesLineEdit = new QTextEdit(this);
    check = new QCheckBox(this);

    NameLineEdit->setFixedSize(300, 20);
    AttributesLineEdit->setFixedSize(300, 50);
    check->setText("Click if this is a final state.");

    QVBoxLayout *Name = new QVBoxLayout;
    Name->addWidget(NameLabel);
    Name->addWidget(NameLineEdit);
    Name->setAlignment(Name, Qt::AlignTop);

    QVBoxLayout *Attributes = new QVBoxLayout;
    Attributes->addWidget(AttributesLabel);
    Attributes->addWidget(AttributesLineEdit);
    Attributes->setAlignment(Attributes, Qt::AlignCenter);

    QVBoxLayout *Check = new QVBoxLayout;
    Check->addWidget(check);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(Name);
    mainLayout->addLayout(Attributes);
    mainLayout->addLayout(Check);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

void StateObjectDialog::okButtonClicked() {
    emit nameSet(NameLineEdit->text());
    emit attributesSet(AttributesLineEdit->toPlainText());
    emit finalSet(check->isChecked());
    this->close();
}

void StateObjectDialog::setName(QString newName) {
    NameLineEdit->setText(newName);
}

void StateObjectDialog::setAttributes(QString newAttributes) {
    AttributesLineEdit->setText(newAttributes);
}

void StateObjectDialog::setFinal(bool state)
{
    check->setChecked(state);
}

QDialog * StateObject::getDialog() {
  StateObjectDialog *dialog = new StateObjectDialog;
  dialog->setFixedSize(450, 200);
  dialog->setName(m_name);
  dialog->setAttributes(m_attributes);
  dialog->setFinal(m_finalstate);
  connect(dialog, SIGNAL(nameSet(QString)),
          this, SLOT(setName(QString)));
  connect(dialog, SIGNAL(attributesSet(QString)),
          this, SLOT(setAttributes(QString)));
  connect(dialog, SIGNAL(finalSet(bool)),
          this, SLOT(setFinal(bool)));
  return dialog;
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
  this->length = 25;
  this->height = 25;
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
  painter.drawEllipse(position, (length-10) / 2, (height-10) / 2);
}


TransitionConnection::TransitionConnection() {
  extensionLength = -30.0;
}

QDialog *TransitionConnection::getDialog()
{
  TransitionConnectionDialog *dialog = new TransitionConnectionDialog;
  dialog->setTextValue(m_text);
  connect(dialog, SIGNAL(textValueSelected(QString)),
          this, SLOT(setText(QString)));
  return dialog;
}

void TransitionConnection::draw(QPainter &painter) {
  if (connectedObjects.size() != 2) {
    qDebug() << "TransitionConnection::draw Error: Only " << connectedObjects.size() << " connected objects!";
    return;
  }
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

    QFontMetrics fm = painter.fontMetrics();
    int temp = fm.width(m_text);
    // calculates the midpoint between the objects
    int x = (pt1.x() + pt2.x()) / 2;
    int y = (pt1.y() + pt2.y()) / 2;
    QPoint textPos(x,y);
    int xdist = (pt1.x()-pt2.x())*(pt1.x()-pt2.x());
    int ydist = (pt1.y()-pt2.y())*(pt1.y()-pt2.y());
    if(xdist > ydist && pt1.x() > pt2.x()){
        painter.drawText(textPos.x()-(temp/2),textPos.y()+20, m_text);
    }
    else if(xdist > ydist && pt1.x() < pt2.x()){
        painter.drawText(textPos.x()-(temp/2),textPos.y()-10, m_text);
    }
    else{
        painter.drawText(textPos.x()-(temp+5),textPos.y(), m_text);
    }
    drawArrow(painter);
  }
  /*
  BaseNode *obj1, *obj2;
  std::list<BaseNode*>::iterator it = connectedObjects.begin();
  obj1 = *(it);
  it++;
  obj2 = *(it);

  pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
  pt2 = obj2->getClosestConnectionPoint(obj1->getPosition());

  int x = (pt1.x() + pt2.x()) / 2;
  int y = (pt1.y() + pt2.y()) / 2;
  QPoint textPos(x,y);

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
  painter.drawText(textPos, m_text);
  drawArrow(painter);
  */
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

void TransitionConnection::drawArrow(QPainter &painter)
{
    const double arrowAngle = 0.75;
    lineangle = mathfunctions::computeAngle(pt1, pt2);
    painter.drawLine(pt2.x(), pt2.y(),
                     pt2.x() + 10 * sin(lineangle - arrowAngle),
                     pt2.y() + 10 * cos(lineangle - arrowAngle));
    painter.drawLine(pt2.x(), pt2.y(),
                     pt2.x() - 10 * sin(lineangle + arrowAngle),
                     pt2.y() - 10 * cos(lineangle + arrowAngle));
}

TransitionConnectionDialog::TransitionConnectionDialog(QWidget *parent)
  :QInputDialog(parent)
{
  setLabelText("Tansition Text:");
  setWindowTitle("Transition Properties");
}

void StateSelfConnection::draw(QPainter &painter)
{

      BaseNode *obj1, *obj2;
      std::list<BaseNode*>::iterator it = connectedObjects.begin();
      obj1 = *it;
      obj2 = *it;
      it++;

      pt1 = obj1->returnConnectionPoint(1);
      pt4 = obj2->returnConnectionPoint(2);

      painter.setPen(Qt::black);
      if (selected == true) {
        QPen selectPen;
        selectPen.setWidth(2);
        selectPen.setColor(Qt::blue);
        painter.setPen(selectPen);
      }

    painter.drawLine(pt1.x(),pt1.y()+10,pt1.x()+15, pt1.y()+10);
    painter.drawLine(pt1.x()+15,pt1.y()+10,pt1.x()+15, pt4.y()+15);
    painter.drawLine(pt1.x()+15,pt4.y()+15,pt4.x()+10, pt4.y()+15);
    painter.drawLine(pt4.x()+10,pt4.y()+15,pt4.x()+10, pt4.y());
    painter.drawLine(pt4.x()+5,pt4.y()+5,pt4.x()+10,pt4.y());
    painter.drawLine(pt4.x()+15,pt4.y()+5,pt4.x()+10,pt4.y());
    painter.drawText(pt4.x()+20,pt4.y()+30,m_text);
}

StateSelfConnectionDialog::StateSelfConnectionDialog(QWidget *parent)
                           :QInputDialog(parent) {
  setCancelButtonText("Cancel");
  setLabelText("Connector Name:");
  setWindowTitle("Connector Properties");
  setOkButtonText("Ok");
}

QDialog *StateSelfConnection::getDialog()
{
    StateSelfConnectionDialog *dialog = new StateSelfConnectionDialog;
    dialog->setTextValue(m_text);
    connect(dialog, SIGNAL(textValueSelected(QString)),
            this, SLOT(setName(QString)));
    return dialog;
}
