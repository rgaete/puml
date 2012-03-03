// Copyright (C) 2011-2012 pUML Group

/*! @file UMlnodes_class.h
    @brief Defines concrete Objectnodes and Connectionnodes that specific to
           class diagrams.
  */
#ifndef SRC_UMLNODES_CLASS_H_
#define SRC_UMLNODES_CLASS_H_

#include <QInputDialog>
#include "./nodes.h"

/*! @brief This defines a custom dialog for a ClassBoxObject
*/
class ClassBoxObjectDialog : public QInputDialog {
  Q_OBJECT

  public:
    explicit ClassBoxObjectDialog(QWidget *parent = 0);
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
    QString getIconPath() { return QString(":/Images/oval.png"); }
    QString getText() { return "ClassBox"; }
    DiagramType getDiagramType() { return Class; }

    void draw(QPainter &painter);  // NOLINT


  public slots:
    void setName(QString newName) { this->name = newName; }

  private:
    int radius;
    QString name;
};

/*! @brief The properties dialog for class connections
 */
class ClassConnectionDialog : public QInputDialog {
};

/*! @brief This concrete class defines ...
 */
class ClassConnection : public SquareConnectionNode {
  public:
    BaseNode* clone() { return new ClassConnection; }
    QDialog* getDialog() { return new ClassConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Class Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }
};

#endif  // SRC_UMLNODES_CLASS_H_
