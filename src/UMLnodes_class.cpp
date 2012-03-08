// Copyright (C) 2011-2012 pUML Group

#include <list>

#include "./UMLnodes_class.h"


ClassBoxObject::ClassBoxObject() {
  this->length = 140;
  this->height = 100;
}

void ClassBoxObject::draw(QPainter &painter) {  // NOLINT
  // Always call this ObjectNode's draw function because it
  // draws the selection boxes as needed.
  ObjectNode::draw(painter);
  QRect frame(position.x() - length / 2,
            position.y() - height / 2,
            length, height);
  // box fill
  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.setBackground(Qt::white);
  painter.drawRect(frame);

  //Class section
  int nameLength = className.size();
  QRect classSection(position.x() - nameLength*5,   //center ClassName text
                     position.y() - height / 2,
                     length, height);

  const QFont boldFont("Arial",10, QFont::Bold);
  painter.setFont(boldFont);                        //className set to Bold
  painter.drawText(classSection, className);

  //Attributes section
  const QFont normalFont("Arial",10,QFont::Normal);
  painter.setFont(normalFont);

  QRect attributesSection(position.x() - length / 2,
                          position.y() - height / 5,
                          length, height);
  painter.drawLine(position.x()-length / 2,position.y() - height / 5,
                   position.x()+length / 2, position.y() - height / 5);
  painter.drawText(attributesSection, attributes);

  //Methods section
  QRect methodsSection(position.x() - length / 2,
                       position.y() + height / 5,
                       length, height);
  painter.drawLine(position.x()-length / 2,position.y() + height / 5,
                   position.x()+length / 2, position.y() + height / 5);
  painter.drawText(methodsSection, methods);
}

ClassBoxObjectDialog::ClassBoxObjectDialog(QWidget *parent)
                     :QDialog(parent) {

    okButton = new QPushButton(tr("Ok"),this);

    ClassNameLabel = new QLabel(tr("Class Name:"), this);
    AttributesLabel = new QLabel(tr("Attributes:"), this);
    MethodsLabel = new QLabel(tr("Methods:"), this);

    ClassNameLineEdit = new QTextEdit(this);
    AttributesLineEdit = new QTextEdit(this);
    MethodsLineEdit = new QTextEdit(this);

    ClassNameLineEdit->setFixedSize(300, 50);
    AttributesLineEdit->setFixedSize(300, 50);
    MethodsLineEdit->setFixedSize(300, 50);

    QVBoxLayout *ClassName = new QVBoxLayout;
    ClassName->addWidget(ClassNameLabel);
    ClassName->addWidget(ClassNameLineEdit);
    ClassName->setAlignment(ClassName,Qt::AlignTop);

    QVBoxLayout *Attributes = new QVBoxLayout;
    Attributes->addWidget(AttributesLabel);
    Attributes->addWidget(AttributesLineEdit);
    Attributes->setAlignment(Attributes,Qt::AlignCenter);

    QVBoxLayout *Methods = new QVBoxLayout;
    Methods->addWidget(MethodsLabel);
    Methods->addWidget(MethodsLineEdit);
    Methods->setAlignment(Methods,Qt::AlignBottom);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(ClassName);
    mainLayout->addLayout(Attributes);
    mainLayout->addLayout(Methods);
    mainLayout->addWidget(okButton, 0, Qt::AlignBottom);
    connect(okButton, SIGNAL(clicked()),this, SLOT(okButtonClicked()));
}

void ClassBoxObjectDialog::okButtonClicked()
{
    emit classNameSet(ClassNameLineEdit->toPlainText());
    emit attributesSet(AttributesLineEdit->toPlainText());
    emit methodsSet(MethodsLineEdit->toPlainText());
    this->close();
}
void ClassBoxObjectDialog::setClassName(QString newClassName)
{
    ClassNameLineEdit->setText(newClassName);
}
void ClassBoxObjectDialog::setAttributes(QString newAttributes)
{
    AttributesLineEdit->setText(newAttributes);
}
void ClassBoxObjectDialog::setMethods(QString newMethods)
{
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
