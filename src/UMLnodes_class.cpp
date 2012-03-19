// Copyright (C) 2011-2012 pUML Group

#include <list>
#include <iostream>
using namespace std;
#include "./UMLnodes_class.h"


ClassBoxObject::ClassBoxObject() {
  this->length = 60;
  this->height = 45;
  this->classHeight = 15;
  this->attributeHeight = 15;
  this->methodHeight = 15;
}

void ClassBoxObject::draw(QPainter &painter) {  // NOLINT
    //for resizing the ClassBoxObject
    QFontMetrics fm = painter.fontMetrics();
    int temp = fm.width(this->className);

    //finding length and heights of attributes/methods strings
    //first loop specifically for attributes
    int alength=0,aheight=0,mlength=0,mheight=0,max=0, len=0;
    for(int i=0; i < attributes.length(); i++){
        if(attributes[i] == '\n' || i == attributes.length()-1){
            if(max < len)
                max = len;
            len=0;
            aheight += 1;
        }
        else
            len += 1;
    }
    alength = max;
    max = 0; len = 0;
    //this loop for length and height of methods
    for(int i=0; i < methods.length(); i++){
        if(methods[i] == '\n' || i == methods.length()-1){
            if(max < len)
                max = len;
            len=0;
            mheight += 1;
        }
        else
            len += 1;
    }
    mlength = max;
    max = 0; len = 0;

    //changes the lengths appropriately if need be.
    if(temp >= length-40){
        temp = temp - (length-40);
        temp = temp + length;
        this->length = temp;
    }
    else if((alength*10) >= length-5 || (mlength*10) >= length-5){
        if(mlength > alength)
            temp = mlength*6;
        else
            temp = alength*6;
        temp = temp - (length-5);
        temp = temp + length;
        this->length = temp;
    }
    else{
        this->length = 60;
    }

    //changes the height of the boxes if need be.
    temp = max = 15;
    if(attributeHeight <= (aheight*15)){
        temp = aheight*15;
        this->attributeHeight = temp;
    }
    if(methodHeight <= (mheight*15)){
        max = mheight*15;
        this->methodHeight = max;
    }
    temp = temp + max + classHeight;
    if(temp >= height){
        this->height = temp;
    }
    else{
        this->methodHeight=15;
        this->attributeHeight=15;
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
                       className);

      // Attributes section
      const QFont normalFont;
      painter.setFont(normalFont);

  QRect attributesSection(position.x() - (length / 2) + 4,
                          position.y() - (height / 2) + classHeight,
                          length, height);
  painter.drawLine(position.x() - length / 2, position.y() - (height / 2) + classHeight,
                   position.x() + length / 2, position.y() - (height / 2) + classHeight);
  painter.drawText(attributesSection, attributes);


  // Methods section
  QRect methodsSection(position.x() - (length / 2) + 4,
                       position.y() - (height / 2) + classHeight + attributeHeight,
                       length, height);
  painter.drawLine(position.x() - length / 2, position.y() - (height / 2) + classHeight + attributeHeight,
                   position.x() + length / 2, position.y() - (height / 2) + classHeight + attributeHeight);
  painter.drawText(methodsSection, methods);

  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
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
  dialog->setClassName(className);
  dialog->setAttributes(attributes);
  dialog->setMethods(methods);
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
}

