#ifndef UMLNODES_COLLAB_H
#define UMLNODES_COLLAB_H


#include <QComboBox>
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
  Q_PROPERTY(QString name READ name WRITE setName)

  public:
    StickPersonCollabObject();
    BaseNode* clone() { return new StickPersonCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/stickman.png"); }
    QString getText() { return "Stick Person"; }
    DiagramType getDiagramType() { return Collaboration; }
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


/*! @brief This concrete class is the BoxCollabObject node
 */
class BoxCollabObject : public ObjectNode {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)

  public:
    BoxCollabObject();
    BaseNode* clone() { return new BoxCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/rectangle.png"); }
    QString getText() { return "Collaboration Box"; }
    DiagramType getDiagramType() { return Collaboration; }
    void draw(QPainter &painter);  // NOLINT

    QString name() { return m_name; }
  public slots:
    void setName(QString newName) { this->m_name = newName; }
  private:
    QString m_name;
};

/*! @brief The properties dialog for collaboration boxes
 */
class BoxCollabObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit BoxCollabObjectDialog(QWidget *parent = 0);
};


/*! @brief This concrete class is the MultiBoxCollabObject node
 */

class MultiBoxCollabObject : public ObjectNode {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName)

  public:
    MultiBoxCollabObject();
    BaseNode* clone() { return new MultiBoxCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/multibox.png"); }
    QString getText() { return "Collaboration Multibox"; }
    DiagramType getDiagramType() { return Collaboration; }
    void draw(QPainter &painter);  // NOLINT

    QString name() { return m_name; }
  public slots:
    void setName(QString newName) { this->m_name = newName; }
  private:
    QString m_name;
};

/*! @brief The properties dialog for collaboration multiboxes
 */
class MultiBoxCollabObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit MultiBoxCollabObjectDialog(QWidget *parent = 0);
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
  Q_PROPERTY(QString text READ text WRITE setName)

  public:
    BaseNode* clone() { return new CollabConnection; }
    QDialog* getDialog();// { return new CollabConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Collaboration Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Collaboration; }

    QString text() { return m_text; }

    int FindDirection(QPoint point1, QPoint point2, QPoint temppoint1, QPoint temppoint2);
    void DrawArrow(QPainter &painter, QPoint point, QPoint point2, QPoint temppoint1, QPoint temppoint2);
  public slots:
    void setName(QString newName) { this->m_text = newName; }
  private:
    QString m_text;
    QPoint textpos;
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
  Q_PROPERTY(QString text READ text WRITE setName)

  public:
    BaseNode* clone() { return new CollabSelfConnection; }
    QDialog* getDialog();// { return new CollabConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Collaboration Self Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Collaboration; }

    QString text() { return m_text; }

    int FindDirection(QPoint point1, QPoint point2, QPoint temppoint1, QPoint temppoint2);
    void DrawArrow(QPainter &painter, QPoint point, QPoint point2, QPoint temppoint1, QPoint temppoint2);
  public slots:
    void setName(QString newName) { this->m_text = newName; }
  private:
    QString m_text;
    QPoint textpos;


};



#endif // UMLNODES_COLLAB_H
