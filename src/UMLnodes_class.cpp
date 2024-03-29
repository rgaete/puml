// Copyright (C) 2011-2012 pUML Group

#include <list>
#include <iostream>
#include "mathfunctions.h"
using namespace std;
#include "./UMLnodes_class.h"


ClassBoxObject::ClassBoxObject() {
  this->length = 60;
  this->height = 45;
  this->classHeight = 15;
  this->attributeHeight = 15;
  this->methodHeight = 15;
}

/*
QDomElement ClassBoxObject::to_xml(QDomDocument &doc, QDomElement &doc_root) {

fprintf(stderr, "Got here\n");
  QDomElement node = BaseNode::to_xml(doc, doc_root);
  node.setAttribute(QString("classHeight"), QString::number(classHeight));
  node.setAttribute(QString("attributeHeight"),
                    QString::number(attributeHeight));
  node.setAttribute(QString("methodHeight"), QString::number(methodHeight));
  node.setAttribute(QString("radius"), QString::number(radius));
  node.setAttribute(QString("className"), m_className);
  node.setAttribute(QString("attributes"), m_attributes);
  node.setAttribute(QString("methods"), m_methods);
  return node;

}

*/
void ClassBoxObject::draw(QPainter &painter) {  // NOLINT
    //This is for resizing the ClassBoxObject
    //The variables being created here hold the height and length
    //in pixels of the strings
    QFontMetrics fm = painter.fontMetrics();

    int temp;
    int width = fm.width(this->m_className);
    int alength,aheight,mlength,mheight,max=0;

    alength = stringLength(this->m_attributes);
    mlength = stringLength(this->m_methods);

    aheight = stringHeight(this->m_attributes);
    mheight = stringHeight(this->m_methods);

    //figures out if the new strings inputed into the dialog
    //are bigger or smaller than before and resizes the objects
    //height and lengths accordingly, first checks the lengths
    if( alength+10 >= length-10 || mlength+10 >= length-10 ||
        alength+10 >= 50 || mlength+10 >= 50 || width >= length-40 ||
        width >= 20){
        if(mlength > alength && mlength > width && mlength > 60){
            temp = mlength;
            temp = temp - (length-5);
            temp = temp + length;
        }
        else if (alength > mlength && alength > width && alength > 60){
            temp = alength;
            temp = temp - (length-5);
            temp = temp + length;
        }
        else{
            temp = width;
            temp = temp - (length-40);
            temp = temp + length;
        }
        this->length = temp;
    }
    else{
        this->length = 60;
    }

    //here is the checks to see if the height needs adjustment
    temp = max = 15;
    if(aheight >= attributeHeight || aheight >=15){
        temp = aheight;
        this->attributeHeight = temp;
    }
    else{
        this->attributeHeight = 15;
    }
    if(mheight >= methodHeight || mheight >=15){
        max = mheight;
        this->methodHeight = max;
    }
    else{
        this->methodHeight = 15;
    }
    temp = temp + max + classHeight;
    if(temp >= height || temp >= 45){
        this->height = temp;
    }
    else{
        this->height = 45;
    }

  QRect classFrame(position.x() - length / 2,
                   position.y() - height / 2,
                   length, height);
  // box fill
  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.setBackground(Qt::white);
  painter.drawRect(classFrame);

  // Class section
  QRect classSection(position.x() - length/2 , position.y() - (height/2),
                     length, classHeight);

  QFont boldFont;
  boldFont.setBold(true);
  painter.setFont(boldFont);       // className set to Bold
  painter.drawText(classSection,
                   Qt::AlignCenter | Qt::AlignHCenter | Qt::TextDontClip,
                   m_className);

  // Attributes section
  const QFont normalFont;
  painter.setFont(normalFont);

  QRect attributesSection(position.x() - (length / 2) + 4,
                          position.y() - (height / 2) + classHeight + 2,
                          length, height);
  painter.drawLine(position.x() - length / 2, position.y() - (height / 2) + classHeight,
                   position.x() + length / 2, position.y() - (height / 2) + classHeight);
  painter.drawText(attributesSection, m_attributes);


  // Methods section
  QRect methodsSection(position.x() - (length / 2) + 4,
                       position.y() - (height / 2) + classHeight + attributeHeight + 2,
                       length, height);
  painter.drawLine(position.x() - length / 2, position.y() - (height / 2) + classHeight + attributeHeight,
                   position.x() + length / 2, position.y() - (height / 2) + classHeight + attributeHeight);
  painter.drawText(methodsSection, m_methods);

  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  BaseNode::setUpConnectionPoints();
  ObjectNode::draw(painter);
}

ClassBoxObjectDialog::ClassBoxObjectDialog(QWidget *parent)
                     :QDialog(parent) {
    okButton = new QPushButton(tr("Ok"), this);

    ClassNameLabel = new QLabel(tr("Class Name:"), this);
    AttributesLabel = new QLabel(tr("Attributes:"), this);
    MethodsLabel = new QLabel(tr("Methods:"), this);

    ClassNameLineEdit = new QLineEdit(this);
    AttributesLineEdit = new QTextEdit(this);
    MethodsLineEdit = new QTextEdit(this);

    ClassNameLineEdit->setFixedSize(300, 20);
    AttributesLineEdit->setFixedSize(300, 50);
    MethodsLineEdit->setFixedSize(300, 50);

    QVBoxLayout *ClassName = new QVBoxLayout;
    ClassName->addWidget(ClassNameLabel);
    ClassName->addWidget(ClassNameLineEdit);
    ClassName->setAlignment(ClassName, Qt::AlignTop);

    QVBoxLayout *Attributes = new QVBoxLayout;
    Attributes->addWidget(AttributesLabel);
    Attributes->addWidget(AttributesLineEdit);
    Attributes->setAlignment(Attributes, Qt::AlignCenter);

    QVBoxLayout *Methods = new QVBoxLayout;
    Methods->addWidget(MethodsLabel);
    Methods->addWidget(MethodsLineEdit);
    Methods->setAlignment(Methods, Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(ClassName);
    mainLayout->addLayout(Attributes);
    mainLayout->addLayout(Methods);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

void ClassBoxObjectDialog::okButtonClicked() {
    emit classNameSet(ClassNameLineEdit->text());
    emit attributesSet(AttributesLineEdit->toPlainText());
    emit methodsSet(MethodsLineEdit->toPlainText());
    this->close();
}

void ClassBoxObjectDialog::setClassName(QString newClassName) {
    ClassNameLineEdit->setText(newClassName);
}

void ClassBoxObjectDialog::setAttributes(QString newAttributes) {
    AttributesLineEdit->setText(newAttributes);
}

void ClassBoxObjectDialog::setMethods(QString newMethods) {
    MethodsLineEdit->setText(newMethods);
}

QDialog * ClassBoxObject::getDialog() {
  ClassBoxObjectDialog *dialog = new ClassBoxObjectDialog;
  dialog->setFixedSize(450, 300);
  dialog->setClassName(m_className);
  dialog->setAttributes(m_attributes);
  dialog->setMethods(m_methods);
  connect(dialog, SIGNAL(classNameSet(QString)),
          this, SLOT(setClassName(QString)));
  connect(dialog, SIGNAL(attributesSet(QString)),
          this, SLOT(setAttributes(QString)));
  connect(dialog, SIGNAL(methodsSet(QString)),
          this, SLOT(setMethods(QString)));
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

  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(this->m_name);

  QFontMetrics fm1 = painter.fontMetrics();
  int temp1 = fm1.width(this->m_end);

  QFontMetrics fm2 = painter.fontMetrics();
  int temp2 = fm2.width(this->m_start);

  if(pt1.x() != obj1 -> getPosition().x()){ //East West Text Placement
    if(pt1.x() < pt4.x() && pt1.y() > pt4.y()){
        painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-7-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x() -temp/2 , pt2.y()+15, m_name);
    }
    else if(pt1.x() < pt4.x() && pt1.y() <= pt4.y()){
        painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-7-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x() -temp/2 , pt2.y()-7, m_name);
    }
    else if(pt1.x() > pt4.x() && pt1.y() >= pt4.y()){
        painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()+7, pt4.y()-5, m_end);
        painter.drawText(pt2.x() - temp/2, pt2.y()+15, m_name);
    }
    else if(pt1.x() > pt4.x() && pt1.y() < pt4.y()){
        painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()+7, pt4.y()-5, m_end);
        painter.drawText(pt2.x() - temp/2, pt2.y()-7, m_name);
    }
  }
  else if(pt1.x() == obj1 -> getPosition().x()){    //North South Text Placement
    if(pt1.y() > pt4.y() && pt1.x() <= pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()+15, m_end);
        painter.drawText(pt2.x()+5, pt2.y()+15, m_name);
    }
    else if(pt1.y() > pt4.y() && pt1.x() > pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()+15, m_end);
        painter.drawText(pt2.x()-5-temp, pt2.y()+15, m_name);
    }
    else if(pt1.y() < pt4.y() && pt1.x() <= pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x()+5, pt2.y()-7, m_name);
    }
    else if(pt1.y() < pt4.y() && pt1.x() > pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x()-5-temp, pt2.y()-7, m_name);
    }
  }
}

ClassConnectionDialog::ClassConnectionDialog(QWidget *parent)
                     :QDialog(parent) {
    okButton = new QPushButton(tr("Ok"), this);

    StartLabel = new QLabel(tr("Start of connection multiplicity:"), this);
    NameLabel = new QLabel(tr("Name:"), this);
    EndLabel = new QLabel(tr("End of connection multiplicity:"), this);

    StartLineEdit = new QLineEdit(this);
    NameLineEdit = new QLineEdit(this);
    EndLineEdit = new QLineEdit(this);

    StartLineEdit->setFixedSize(300, 20);
    NameLineEdit->setFixedSize(300, 20);
    EndLineEdit->setFixedSize(300, 20);

    QVBoxLayout *Start = new QVBoxLayout;
    Start->addWidget(StartLabel);
    Start->addWidget(StartLineEdit);
    Start->setAlignment(Start, Qt::AlignTop);

    QVBoxLayout *Name = new QVBoxLayout;
    Name->addWidget(NameLabel);
    Name->addWidget(NameLineEdit);
    Name->setAlignment(Name, Qt::AlignCenter);

    QVBoxLayout *End = new QVBoxLayout;
    End->addWidget(EndLabel);
    End->addWidget(EndLineEdit);
    End->setAlignment(End, Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(Start);
    mainLayout->addLayout(Name);
    mainLayout->addLayout(End);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

QDialog *ClassConnection::getDialog()
{
    ClassConnectionDialog *dialog = new ClassConnectionDialog;
    dialog->setFixedSize(450, 175);
    dialog->setStart(m_start);
    dialog->setName(m_name);
    dialog->setEnd(m_end);
    connect(dialog, SIGNAL(startSet(QString)),
            this, SLOT(setStart(QString)));
    connect(dialog, SIGNAL(nameSet(QString)),
            this, SLOT(setName(QString)));
    connect(dialog, SIGNAL(endSet(QString)),
            this, SLOT(setEnd(QString)));
    return dialog;
}

void ClassConnectionDialog::setStart(QString newStart)
{
    StartLineEdit->setText(newStart);
}

void ClassConnectionDialog::setName(QString newName)
{
    NameLineEdit->setText(newName);
}

void ClassConnectionDialog::setEnd(QString newEnd)
{
    EndLineEdit->setText(newEnd);
}

void ClassConnectionDialog::okButtonClicked()
{
    emit startSet(StartLineEdit->text());
    emit nameSet(NameLineEdit->text());
    emit endSet(EndLineEdit->text());
    this->close();
}

void InheritanceConnection::draw(QPainter& painter) {  // NOLINT
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
  } else if (pt1.x() != obj1 -> getPosition().x()) {  // East or West connection
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

  QFontMetrics fm = painter.fontMetrics();
  int temp = fm.width(this->m_name);

  QFontMetrics fm1 = painter.fontMetrics();
  int temp1 = fm1.width(this->m_end);

  QFontMetrics fm2 = painter.fontMetrics();
  int temp2 = fm2.width(this->m_start);

  if(pt1.x() != obj1 -> getPosition().x()){ //East West Text Placement
    if(pt1.x() < pt4.x() && pt1.y() > pt4.y()){
        painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x() -temp/2 , pt2.y()+15, m_name);
    }
    else if(pt1.x() < pt4.x() && pt1.y() <= pt4.y()){
        painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
        painter.drawText(pt2.x() -temp/2 , pt2.y()-7, m_name);
    }
    else if(pt1.x() > pt4.x() && pt1.y() >= pt4.y()){
        painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
        painter.drawText(pt2.x() - temp/2, pt2.y()+15, m_name);
    }
    else if(pt1.x() > pt4.x() && pt1.y() < pt4.y()){
        painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
        painter.drawText(pt2.x() - temp/2, pt2.y()-7, m_name);
    }
  }
  else if(pt1.x() == obj1 -> getPosition().x()){    //North South Text Placement
    if(pt1.y() > pt4.y() && pt1.x() <= pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
        painter.drawText(pt2.x()+5, pt2.y()+15, m_name);
    }
    else if(pt1.y() > pt4.y() && pt1.x() > pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
        painter.drawText(pt2.x()-5-temp, pt2.y()+15, m_name);
    }
    else if(pt1.y() < pt4.y() && pt1.x() <= pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
        painter.drawText(pt2.x()+5, pt2.y()-7, m_name);
    }
    else if(pt1.y() < pt4.y() && pt1.x() > pt4.x()){
        painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
        painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
        painter.drawText(pt2.x()-5-temp, pt2.y()-7, m_name);
    }

  }

  //If construct checks connection location, then trims the arrow respectively
  if(pt1.x() < obj1 -> getPosition().x()) //East Connection
  {
      pt4.setX(pt4.x() + 8.0);
      painter.drawLine(pt3, pt4);
      pt4.setX(pt4.x() - 8.0 );
  }
  else if(pt1.x() > obj1 -> getPosition().x())  //West Connection
  {
      pt4.setX(pt4.x() - 8.0);
      painter.drawLine(pt3, pt4);
      pt4.setX(pt4.x() + 8.0);
  }
  else if(pt1.y() > obj1 -> getPosition().y())  //North Connection
  {
      pt4.setY(pt4.y() - 8.0);
      painter.drawLine(pt3, pt4);
      pt4.setY(pt4.y() + 8.0);
  }
  else if(pt1.y() < obj1 -> getPosition().y())  //South Connection
  {
      pt4.setY(pt4.y() + 8.0);
      painter.drawLine(pt3, pt4);
      pt4.setY(pt4.y() - 8.0);
  }
  addArrow(painter);
}
void InheritanceConnection::addArrow(QPainter &painter) {  // NOLINT
  double arrowAngle = 0.8;
  if(pt4.y()>pt3.y())
  {
      arrowAngle=-arrowAngle;   //reverse arrow point
  }
  lineAngle = mathfunctions::computeAngle(pt3, pt4);
  painter.drawLine(pt4.x(), pt4.y(),
                   pt4.x() + 10 * sin(lineAngle - arrowAngle),
                   pt4.y() + 10 * cos(lineAngle - arrowAngle));
  painter.drawLine(pt4.x(), pt4.y(),
                   pt4.x() - 10 * sin(lineAngle + arrowAngle),
                   pt4.y() - 10 * cos(lineAngle + arrowAngle));
  painter.drawLine( pt4.x() + 10 * sin(lineAngle - arrowAngle),
                    pt4.y() + 10 * cos(lineAngle - arrowAngle),
                    pt4.x() - 10 * sin(lineAngle + arrowAngle),
                    pt4.y() - 10 * cos(lineAngle + arrowAngle));
}


InheritanceConnectionDialog::InheritanceConnectionDialog(QWidget *parent)
                     :QDialog(parent) {
    okButton = new QPushButton(tr("Ok"), this);

    StartLabel = new QLabel(tr("Start of connection multiplicity:"), this);
    NameLabel = new QLabel(tr("Name:"), this);
    EndLabel = new QLabel(tr("End of connection multiplicity:"), this);

    StartLineEdit = new QLineEdit(this);
    NameLineEdit = new QLineEdit(this);
    EndLineEdit = new QLineEdit(this);

    StartLineEdit->setFixedSize(300, 20);
    NameLineEdit->setFixedSize(300, 20);
    EndLineEdit->setFixedSize(300, 20);

    QVBoxLayout *Start = new QVBoxLayout;
    Start->addWidget(StartLabel);
    Start->addWidget(StartLineEdit);
    Start->setAlignment(Start, Qt::AlignTop);

    QVBoxLayout *Name = new QVBoxLayout;
    Name->addWidget(NameLabel);
    Name->addWidget(NameLineEdit);
    Name->setAlignment(Name, Qt::AlignCenter);

    QVBoxLayout *End = new QVBoxLayout;
    End->addWidget(EndLabel);
    End->addWidget(EndLineEdit);
    End->setAlignment(End, Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(Start);
    mainLayout->addLayout(Name);
    mainLayout->addLayout(End);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

QDialog *InheritanceConnection::getDialog()
{
    InheritanceConnectionDialog *dialog = new InheritanceConnectionDialog;
    dialog->setFixedSize(450, 175);
    dialog->setStart(m_start);
    dialog->setName(m_name);
    dialog->setEnd(m_end);
    connect(dialog, SIGNAL(startSet(QString)),
            this, SLOT(setStart(QString)));
    connect(dialog, SIGNAL(nameSet(QString)),
            this, SLOT(setName(QString)));
    connect(dialog, SIGNAL(endSet(QString)),
            this, SLOT(setEnd(QString)));
    return dialog;
}

void InheritanceConnectionDialog::setStart(QString newStart)
{
    StartLineEdit->setText(newStart);
}

void InheritanceConnectionDialog::setName(QString newName)
{
    NameLineEdit->setText(newName);
}

void InheritanceConnectionDialog::setEnd(QString newEnd)
{
    EndLineEdit->setText(newEnd);
}

void InheritanceConnectionDialog::okButtonClicked()
{
    emit startSet(StartLineEdit->text());
    emit nameSet(NameLineEdit->text());
    emit endSet(EndLineEdit->text());
    this->close();
}

void AggregationConnection::draw(QPainter &painter)
{
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
    } else if (pt1.x() != obj1 -> getPosition().x()) {  // East or West connection
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

    QFontMetrics fm = painter.fontMetrics();
    int temp = fm.width(this->m_name);

    QFontMetrics fm1 = painter.fontMetrics();
    int temp1 = fm1.width(this->m_end);

    QFontMetrics fm2 = painter.fontMetrics();
    int temp2 = fm2.width(this->m_start);

    if(pt1.x() != obj1 -> getPosition().x()){ //East West Text Placement
      if(pt1.x() < pt4.x() && pt1.y() > pt4.y()){
          painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
          painter.drawText(pt2.x() -temp/2 , pt2.y()+15, m_name);
      }
      else if(pt1.x() < pt4.x() && pt1.y() <= pt4.y()){
          painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
          painter.drawText(pt2.x() -temp/2 , pt2.y()-7, m_name);
      }
      else if(pt1.x() > pt4.x() && pt1.y() >= pt4.y()){
          painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
          painter.drawText(pt2.x() - temp/2, pt2.y()+15, m_name);
      }
      else if(pt1.x() > pt4.x() && pt1.y() < pt4.y()){
          painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
          painter.drawText(pt2.x() - temp/2, pt2.y()-7, m_name);
      }
    }
    else if(pt1.x() == obj1 -> getPosition().x()){    //North South Text Placement
      if(pt1.y() > pt4.y() && pt1.x() <= pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
          painter.drawText(pt2.x()+5, pt2.y()+15, m_name);
      }
      else if(pt1.y() > pt4.y() && pt1.x() > pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
          painter.drawText(pt2.x()-5-temp, pt2.y()+15, m_name);
      }
      else if(pt1.y() < pt4.y() && pt1.x() <= pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
          painter.drawText(pt2.x()+5, pt2.y()-7, m_name);
      }
      else if(pt1.y() < pt4.y() && pt1.x() > pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
          painter.drawText(pt2.x()-5-temp, pt2.y()-7, m_name);
      }

    }

    //If construct checks connection location, then trims the arrow respectively
    if(pt1.x() < obj1 -> getPosition().x()) //East Connection
    {
        pt4.setX(pt4.x() + 20.0);
        painter.drawLine(pt3, pt4);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()+5);
        pt4.setX(pt4.x() - 20.0 );
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()+5);
    }
    else if(pt1.x() > obj1 -> getPosition().x())  //West Connection
    {
        pt4.setX(pt4.x() - 20.0);
        painter.drawLine(pt3, pt4);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()+5);
        pt4.setX(pt4.x() + 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()+5);
    }
    else if(pt1.y() > obj1 -> getPosition().y())  //North Connection
    {
        pt4.setY(pt4.y() - 20.0);
        painter.drawLine(pt3, pt4);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()+10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()+10);
        pt4.setY(pt4.y() + 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()-10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()-10);
    }
    else if(pt1.y() < obj1 -> getPosition().y())  //South Connection
    {
        pt4.setY(pt4.y() + 20.0);
        painter.drawLine(pt3, pt4);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()-10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()-10);
        pt4.setY(pt4.y() - 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()+10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()+10);
    }
}

AggregationConnectionDialog::AggregationConnectionDialog(QWidget *parent)
                     :QDialog(parent) {
    okButton = new QPushButton(tr("Ok"), this);

    StartLabel = new QLabel(tr("Start of connection multiplicity:"), this);
    NameLabel = new QLabel(tr("Name:"), this);
    EndLabel = new QLabel(tr("End of connection multiplicity:"), this);

    StartLineEdit = new QLineEdit(this);
    NameLineEdit = new QLineEdit(this);
    EndLineEdit = new QLineEdit(this);

    StartLineEdit->setFixedSize(300, 20);
    NameLineEdit->setFixedSize(300, 20);
    EndLineEdit->setFixedSize(300, 20);

    QVBoxLayout *Start = new QVBoxLayout;
    Start->addWidget(StartLabel);
    Start->addWidget(StartLineEdit);
    Start->setAlignment(Start, Qt::AlignTop);

    QVBoxLayout *Name = new QVBoxLayout;
    Name->addWidget(NameLabel);
    Name->addWidget(NameLineEdit);
    Name->setAlignment(Name, Qt::AlignCenter);

    QVBoxLayout *End = new QVBoxLayout;
    End->addWidget(EndLabel);
    End->addWidget(EndLineEdit);
    End->setAlignment(End, Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(Start);
    mainLayout->addLayout(Name);
    mainLayout->addLayout(End);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

QDialog *AggregationConnection::getDialog()
{
    AggregationConnectionDialog *dialog = new AggregationConnectionDialog;
    dialog->setFixedSize(450, 175);
    dialog->setStart(m_start);
    dialog->setName(m_name);
    dialog->setEnd(m_end);
    connect(dialog, SIGNAL(startSet(QString)),
            this, SLOT(setStart(QString)));
    connect(dialog, SIGNAL(nameSet(QString)),
            this, SLOT(setName(QString)));
    connect(dialog, SIGNAL(endSet(QString)),
            this, SLOT(setEnd(QString)));
    return dialog;
}

void AggregationConnectionDialog::setStart(QString newStart)
{
    StartLineEdit->setText(newStart);
}

void AggregationConnectionDialog::setName(QString newName)
{
    NameLineEdit->setText(newName);
}

void AggregationConnectionDialog::setEnd(QString newEnd)
{
    EndLineEdit->setText(newEnd);
}

void AggregationConnectionDialog::okButtonClicked()
{
    emit startSet(StartLineEdit->text());
    emit nameSet(NameLineEdit->text());
    emit endSet(EndLineEdit->text());
    this->close();
}

//**********

void CompositionConnection::draw(QPainter &painter)
{
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
    } else if (pt1.x() != obj1 -> getPosition().x()) {  // East or West connection
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

    QFontMetrics fm = painter.fontMetrics();
    int temp = fm.width(this->m_name);

    QFontMetrics fm1 = painter.fontMetrics();
    int temp1 = fm1.width(this->m_end);

    QFontMetrics fm2 = painter.fontMetrics();
    int temp2 = fm2.width(this->m_start);

    if(pt1.x() != obj1 -> getPosition().x()){ //East West Text Placement
      if(pt1.x() < pt4.x() && pt1.y() > pt4.y()){
          painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
          painter.drawText(pt2.x() -temp/2 , pt2.y()+15, m_name);
      }
      else if(pt1.x() < pt4.x() && pt1.y() <= pt4.y()){
          painter.drawText(pt1.x()+10, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-15-temp1, pt4.y()-5, m_end);
          painter.drawText(pt2.x() -temp/2 , pt2.y()-7, m_name);
      }
      else if(pt1.x() > pt4.x() && pt1.y() >= pt4.y()){
          painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
          painter.drawText(pt2.x() - temp/2, pt2.y()+15, m_name);
      }
      else if(pt1.x() > pt4.x() && pt1.y() < pt4.y()){
          painter.drawText(pt1.x()-10-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()+15, pt4.y()-5, m_end);
          painter.drawText(pt2.x() - temp/2, pt2.y()-7, m_name);
      }
    }
    else if(pt1.x() == obj1 -> getPosition().x()){    //North South Text Placement
      if(pt1.y() > pt4.y() && pt1.x() <= pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
          painter.drawText(pt2.x()+5, pt2.y()+15, m_name);
      }
      else if(pt1.y() > pt4.y() && pt1.x() > pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()-5, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()+20, m_end);
          painter.drawText(pt2.x()-5-temp, pt2.y()+15, m_name);
      }
      else if(pt1.y() < pt4.y() && pt1.x() <= pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
          painter.drawText(pt2.x()+5, pt2.y()-7, m_name);
      }
      else if(pt1.y() < pt4.y() && pt1.x() > pt4.x()){
          painter.drawText(pt1.x()-5-temp2, pt1.y()+15, m_start);
          painter.drawText(pt4.x()-10-temp1, pt4.y()-12, m_end);
          painter.drawText(pt2.x()-5-temp, pt2.y()-7, m_name);
      }

    }

    QPolygon arrowhead;
    //If construct checks connection location, then trims the arrow respectively
    if(pt1.x() < obj1 -> getPosition().x()) //East Connection
    {
      // draws the last line segment
      pt4.setX(pt4.x() + 20.0);
      painter.drawLine(pt3, pt4);

      arrowhead << pt4;
      arrowhead << QPoint(pt4.x()-10, pt4.y()-5);
      arrowhead << QPoint(pt4.x()-20, pt4.y());
      arrowhead << QPoint(pt4.x()-10, pt4.y()+5);

    }
    else if(pt1.x() > obj1 -> getPosition().x())  //West Connection
    {
        pt4.setX(pt4.x() - 20.0);
        painter.drawLine(pt3, pt4);

        arrowhead << pt4;
        arrowhead << QPoint(pt4.x()+10, pt4.y()-5);
        arrowhead << QPoint(pt4.x()+20, pt4.y());
        arrowhead << QPoint(pt4.x()+10, pt4.y()+5);
        /*
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+10,pt4.y()+5);
        pt4.setX(pt4.x() + 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()-5);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-10,pt4.y()+5);
        */
    }
    else if(pt1.y() > obj1 -> getPosition().y())  //North Connection
    {
        pt4.setY(pt4.y() - 20.0);
        painter.drawLine(pt3, pt4);

        arrowhead << pt4;
        arrowhead << QPoint(pt4.x()+5, pt4.y()+10);
        arrowhead << QPoint(pt4.x(), pt4.y()+20);
        arrowhead << QPoint(pt4.x()-5, pt4.y()+10);

        /*
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()+10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()+10);
        pt4.setY(pt4.y() + 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()-10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()-10);
        */
    }
    else if(pt1.y() < obj1 -> getPosition().y())  //South Connection
    {
        pt4.setY(pt4.y() + 20.0);
        painter.drawLine(pt3, pt4);

        arrowhead << pt4;
        arrowhead << QPoint(pt4.x()+5, pt4.y()-10);
        arrowhead << QPoint(pt4.x(), pt4.y()-20);
        arrowhead << QPoint(pt4.x()-5, pt4.y()-10);

        /*
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()-10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()-10);
        pt4.setY(pt4.y() - 20.0);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()+5,pt4.y()+10);
        painter.drawLine(pt4.x(),pt4.y(),pt4.x()-5,pt4.y()+10);
        */
    }
    painter.setBrush(QBrush(Qt::black));
    painter.drawPolygon(arrowhead);
}

CompositionConnectionDialog::CompositionConnectionDialog(QWidget *parent)
                     :QDialog(parent) {
    okButton = new QPushButton(tr("Ok"), this);

    StartLabel = new QLabel(tr("Start of connection multiplicity:"), this);
    NameLabel = new QLabel(tr("Name:"), this);
    EndLabel = new QLabel(tr("End of connection multiplicity:"), this);

    StartLineEdit = new QLineEdit(this);
    NameLineEdit = new QLineEdit(this);
    EndLineEdit = new QLineEdit(this);

    StartLineEdit->setFixedSize(300, 20);
    NameLineEdit->setFixedSize(300, 20);
    EndLineEdit->setFixedSize(300, 20);

    QHBoxLayout *Start = new QHBoxLayout;
    Start->addWidget(StartLabel);
    Start->addWidget(StartLineEdit);
    Start->setAlignment(Start, Qt::AlignTop);

    QHBoxLayout *Name = new QHBoxLayout;
    Name->addWidget(NameLabel);
    Name->addWidget(NameLineEdit);
    Name->setAlignment(Name, Qt::AlignCenter);

    QHBoxLayout *End = new QHBoxLayout;
    End->addWidget(EndLabel);
    End->addWidget(EndLineEdit);
    End->setAlignment(End, Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(Start);
    mainLayout->addLayout(Name);
    mainLayout->addLayout(End);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
}

QDialog *CompositionConnection::getDialog()
{
    CompositionConnectionDialog *dialog = new CompositionConnectionDialog;
    dialog->setFixedSize(450, 175);
    dialog->setStart(m_start);
    dialog->setName(m_name);
    dialog->setEnd(m_end);
    connect(dialog, SIGNAL(startSet(QString)),
            this, SLOT(setStart(QString)));
    connect(dialog, SIGNAL(nameSet(QString)),
            this, SLOT(setName(QString)));
    connect(dialog, SIGNAL(endSet(QString)),
            this, SLOT(setEnd(QString)));
    return dialog;
}

void CompositionConnectionDialog::setStart(QString newStart)
{
    StartLineEdit->setText(newStart);
}

void CompositionConnectionDialog::setName(QString newName)
{
    NameLineEdit->setText(newName);
}

void CompositionConnectionDialog::setEnd(QString newEnd)
{
    EndLineEdit->setText(newEnd);
}

void CompositionConnectionDialog::okButtonClicked()
{
    emit startSet(StartLineEdit->text());
    emit nameSet(NameLineEdit->text());
    emit endSet(EndLineEdit->text());
    this->close();
}
