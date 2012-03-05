// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_UMLNODES_STATE_H_
#define SRC_UMLNODES_STATE_H_

#include <QInputDialog>
#include "./nodes.h"

/*! @brief This defines a custom dialog for a OvalObject
*/
class StateObjectDialog : public QInputDialog {
  Q_OBJECT

  public:
    explicit StateObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the State node.
 * @sa ObjectNode
 */
class StateObject: public ObjectNode {
  Q_OBJECT

  public:
    StateObject();
    BaseNode* clone() { return new StateObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/circle.png"); }
    QString getText() { return "State"; }
    DiagramType getDiagramType() { return StateChart; }

    void draw(QPainter &painter);  // NOLINT

  public slots:
    void setName(QString newName) { this->name = newName; }

  private:
    int radius;
    QString name;
};

/*! @brief This defines a custom dialog for a OvalObject
*/
class InitialStateObjectDialog : public QInputDialog {
  Q_OBJECT

  public:
    explicit InitialStateObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the State node.
 * @sa ObjectNode
 */
class InitialStateObject: public ObjectNode {
  Q_OBJECT

  public:
    InitialStateObject();
    BaseNode* clone() { return new InitialStateObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/initialstate.png"); }
    QString getText() { return "Initial State"; }
    DiagramType getDiagramType() { return StateChart; }

    void draw(QPainter &painter);  // NOLINT
};

/*! @brief This defines a custom dialog for a OvalObject
*/
class FinalStateObjectDialog : public QInputDialog {
  Q_OBJECT

  public:
    explicit FinalStateObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the State node.
 * @sa ObjectNode
 */
class FinalStateObject: public ObjectNode {
  Q_OBJECT

  public:
    FinalStateObject();
    BaseNode* clone() { return new FinalStateObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/finalstate.png"); }
    QString getText() { return "Final State"; }
    DiagramType getDiagramType() { return StateChart; }

    void draw(QPainter &painter);  // NOLINT
};

#endif  // SRC_UMLNODES_STATE_H_
