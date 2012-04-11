// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_UMLNODES_STATE_H_
#define SRC_UMLNODES_STATE_H_

#include <QInputDialog>
#include "./nodes.h"

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

class StateObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit StateObjectDialog(QWidget *parent = 0);
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
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/initialstate.png"); }
    QString getText() { return "Initial State"; }
    DiagramType getDiagramType() { return StateChart; }

    void draw(QPainter &painter);  // NOLINT
};


/*!
 * @brief This concrete class is the Final State node.
 * @sa ObjectNode
 */
class FinalStateObject: public ObjectNode {
  Q_OBJECT

  public:
    FinalStateObject();
    BaseNode* clone() { return new FinalStateObject; }
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/finalstate.png"); }
    QString getText() { return "Final State"; }
    DiagramType getDiagramType() { return StateChart; }

    void draw(QPainter &painter);  // NOLINT
};

/*! @brief This class provides a custom dialog for an InteractionLineNode.
*/
class TransitionConnectionDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit TransitionConnectionDialog(QWidget *parent = 0);
};

/*! @brief This concrete class defines an Interaction line in a Use
  Case diagram (line from the actor to the use case)
*/
class TransitionConnection : public ConnectionNode {
  Q_OBJECT
  public:
    TransitionConnection();
    BaseNode* clone() { return new TransitionConnection; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Transition Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return StateChart; }
  private:
    void calcExtensionPoint();
    void drawArrow(QPoint begin, QPoint end, double headLength, int radius, QPainter &painter);
    QPoint extensionPoint;
    double extensionLength;
    QString text;
    QPainterPath arc;
  public slots:
    void setText(QString t) { text = t; }

};


#endif  // SRC_UMLNODES_STATE_H_
