#ifndef UMLNODES_COLLAB_H
#define UMLNODES_COLLAB_H


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
    DiagramType getDiagramType() { return UseCase; }

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
    DiagramType getDiagramType() { return UseCase; }
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

class ArrowCollabObjectDialog : public QInputDialog {
  Q_OBJECT
  public:
    explicit ArrowCollabObjectDialog(QWidget *parent = 0);
};
class ArrowCollabObject : public ObjectNode {
  Q_OBJECT
  public:
    ArrowCollabObject();
    BaseNode* clone() { return new ArrowCollabObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/new.png"); }
    QString getText() { return "Arrow"; }
    DiagramType getDiagramType() { return UseCase; }
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


#endif // UMLNODES_COLLAB_H