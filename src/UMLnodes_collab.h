#ifndef UMLNODES_COLLAB_H
#define UMLNODES_COLLAB_H


#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPoint>
#include <time.h>
#include <cmath>
#include "./nodes.h"


/*! @brief This concrete class defines the input dialog for
  a StickPersonCollab.
  @sa StickPersonCollabObject
*/
class StickPersonCollabObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit StickPersonCollabObjectDialog(QWidget *parent = 0);
};

/*!
 * @brief This concrete class is the StickPersonCollab node.
 * @sa ObjectNode
 */
class StickPersonCollabObject : public ObjectNode {
  Q_OBJECT
  public:
    StickPersonCollabObject();
    BaseNode* clone() { return new StickPersonCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/stickman.png"); }
    QString getText() { return "Stick Person"; }
    DiagramType getDiagramType() { return Collaboration; }

    void draw(QPainter &painter);  // NOLINT

  public slots:
    void setName(QString newName) { this->name = newName; }
  private:
    QString name;
    // animation vars
      // 0 == punch, 1 == no punch
    int punchhand;
    time_t start;
    time_t end;
    double dif;

  private slots:
    // void setName(QString newName) { name = newName; }
};


class BoxCollabObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit BoxCollabObjectDialog(QWidget *parent = 0);
};

class BoxCollabObject : public ObjectNode {
  Q_OBJECT
  public:
    BoxCollabObject();
    BaseNode* clone() { return new BoxCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/square.png"); }
    QString getText() { return "Stick Person"; }
    DiagramType getDiagramType() { return Collaboration; }
//change above line!!!!!!!!!
    void draw(QPainter &painter);  // NOLINT
  public slots:
    void setName(QString newName) { this->name = newName; }
  private:
    QString name;
    // animation vars
  private slots:
    // void setName(QString newName) { name = newName; }
};


/*! @brief The properties dialog for square connections
 */
class CollabConnectionDialog : public QInputDialog {
    Q_OBJECT
public:
    explicit CollabConnectionDialog(QWidget *parent = 0);
};

/*! @brief This concrete class defines ...
 */
class CollabConnection : public SquareConnectionNode {
    Q_OBJECT
  public:
    BaseNode* clone() { return new CollabConnection; }
    QDialog* getDialog();// { return new CollabConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Collaboration Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Collaboration; }
    QPoint FindMidPoint(QPoint point1, QPoint point2);
    int FindDirection(QPoint point1, QPoint point2, QPoint temppoint1, QPoint temppoint2);
    void DrawArrow(QPainter &painter, QPoint point, QPoint point2, QPoint temppoint1, QPoint temppoint2);

   private:
    QString text;
    QPoint textpos;
public slots:
    void setName(QString newName) { this->text = newName; }

};


/*! @brief The properties dialog for self connections
 */
class CollabSelfConnectionDialog : public QInputDialog {
    Q_OBJECT
public:
    explicit CollabSelfConnectionDialog(QWidget *parent = 0);
};


/*! @brief This concrete class defines ...
 */
class CollabSelfConnection : public SquareConnectionNode {
    Q_OBJECT
  public:
    BaseNode* clone() { return new CollabSelfConnection; }
    QDialog* getDialog();// { return new CollabConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Collaboration Self Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Collaboration; }
    int FindDirection(QPoint point1, QPoint point2, QPoint temppoint1, QPoint temppoint2);
    void DrawArrow(QPainter &painter, QPoint point, QPoint point2, QPoint temppoint1, QPoint temppoint2);

   private:
    QString text;
    QPoint textpos;
public slots:
    void setName(QString newName) { this->text = newName; }

};



#endif // UMLNODES_COLLAB_H
