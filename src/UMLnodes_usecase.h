// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_UMLNODES_USECASE_H_
#define SRC_UMLNODES_USECASE_H_

#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <time.h>
#include "./nodes.h"

/*! @brief This concrete class defines the input dialog for
  a StickPerson.
  @sa StickPersonObject
*/
class StickPersonObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit StickPersonObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the StickPerson node.
 * @sa ObjectNode
 */
class StickPersonObject : public ObjectNode {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)

  public:
    StickPersonObject();
    BaseNode* clone() { return new StickPersonObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/stickman.png"); }
    QString getText() { return "Stick Person"; }
    DiagramType getDiagramType() { return UseCase; }
    void draw(QPainter &painter);  // NOLINT

    QString name() { return m_name; }
  public slots:
    void setName(QString newName) { this->m_name = newName; }
  private:
    QString m_name;
    // animation vars
      // 0 == punch, 1 == no punch
    int punchhand;
    time_t start;
    time_t end;
    double dif;
};


/*! @brief This defines a custom dialog for a OvalObject
*/
class OvalObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit OvalObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the Oval node.
 * @sa ObjectNode
 */
class OvalObject: public ObjectNode {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)

  public:
    OvalObject();
    BaseNode* clone() { return new OvalObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/oval.png"); }
    QString getText() { return "Use Case"; }
    DiagramType getDiagramType() { return UseCase; }
    void draw(QPainter &painter);  // NOLINT

    QString name() { return m_name; }
  public slots:
    void setName(QString newName) { this->m_name = newName; }
  private:
    int m_radius;
    QString m_name;
};

/*! @brief This concrete class defines an Interaction line in a Use
  Case diagram (line from the actor to the use case)
*/
class InteractionConnection : public ConnectionNode {
  Q_OBJECT
  public:
    BaseNode* clone() { return new InteractionConnection; }
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Interaction Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return UseCase; }
};


/*! @brief This concrete class defines an Extends line in a Use
  Case diagram (line from the actor to the use case)
*/
class ExtendsConnection : public ConnectionNode {
  Q_OBJECT
  public:
    BaseNode* clone() { return new ExtendsConnection; }
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/extends.png"); }
    QString getText() { return "Extends Line"; }
    void addArrow(QPainter &painter);  // NOLINT
    QPoint calculateTextPosition();
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return UseCase; }
};

/*! This concrete class defines an Extends line in a Use
  Case diagram (line from the actor to the use case)
*/
class IncludesConnection : public ConnectionNode {
  Q_OBJECT
  public:
    BaseNode* clone() { return new IncludesConnection; }
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/includes.png"); }
    QString getText() { return "Includes Line"; }
    void addArrow(QPainter &painter);  // NOLINT
    QPoint calculateTextPosition();
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return UseCase; }
};

/*!
*
*/
class UCInheritanceConnection : public ConnectionNode {
  Q_OBJECT

public:
    BaseNode* clone() { return new UCInheritanceConnection; }
    QDialog* getDialog() { return 0; }
    QString getIconPath() { return QString(":/Images/inheritance.png"); }
    QString getText() { return "Inheritance Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return UseCase; }
    void addArrow(QPainter& painter);
private:
    double lineAngle;
};

#endif  // SRC_UMLNODES_USECASE_H_
