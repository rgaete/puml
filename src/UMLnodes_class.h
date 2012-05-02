// Copyright (C) 2011-2012 pUML Group

/*! @file UMlnodes_class.h
    @brief Defines concrete Objectnodes and Connectionnodes that specific to
           class diagrams.
  */
#ifndef SRC_UMLNODES_CLASS_H_
#define SRC_UMLNODES_CLASS_H_

#include <QInputDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "./nodes.h"
// #include "ui_ClassBoxdialog.h"


/*! @brief This defines a custom dialog for a ClassBoxObject
*/
class ClassBoxObjectDialog : public QDialog {
  Q_OBJECT

  public:
    explicit ClassBoxObjectDialog(QWidget *parent = 0);
    void setClassName(QString newClassName);
    void setAttributes(QString newAttributes);
    void setMethods(QString newMethods);
  private slots:
    void okButtonClicked();
  signals:
    void classNameSet(QString newClassName);
    void attributesSet(QString newAttributes);
    void methodsSet(QString newMethods);
  private:
    QLabel *ClassNameLabel;
    QLabel *AttributesLabel;
    QLabel *MethodsLabel;
    QLineEdit *ClassNameLineEdit;
    QTextEdit *AttributesLineEdit;
    QTextEdit *MethodsLineEdit;
    QPushButton *okButton;
};

/*!
 * @brief This concrete class is the ClassBox node.
 * @sa ObjectNode
 */
class ClassBoxObject: public ObjectNode {
  Q_OBJECT

  public:
    ClassBoxObject();
    BaseNode* clone() { return new ClassBoxObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/class.png"); }
    QString getText() { return "ClassBox"; }
    DiagramType getDiagramType() { return Class; }
    void draw(QPainter &painter);  // NOLINT

  public slots:
    void setClassName(QString newClassName) { this->className = newClassName; }
    void setAttributes(QString newAttributes) {
      this->attributes = newAttributes;
    }
    void setMethods(QString newMethods) { this->methods = newMethods; }

  private:
    int classHeight;
    int attributeHeight;
    int methodHeight;
    int radius;
    QString className;
    QString attributes;
    QString methods;
};

/*! @brief The properties dialog for class connections
 */
class ClassConnectionDialog : public QInputDialog {
};
class InheritanceConnectionDialog : public QInputDialog {
};

/*! @brief This concrete class defines ...
 */
class ClassConnection : public SquareConnectionNode {
  Q_OBJECT
  public:
    BaseNode* clone() { return new ClassConnection; }
    QDialog* getDialog() { return new ClassConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Class Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }
};

class InheritanceConnection : public SquareConnectionNode {
  Q_OBJECT
public:
    BaseNode* clone() { return new InheritanceConnection; }
    QDialog* getDialog() { return new InheritanceConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Inheritance Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }
    void addArrow(QPainter& painter);
private:
    double lineAngle;
};

#endif  // SRC_UMLNODES_CLASS_H_
