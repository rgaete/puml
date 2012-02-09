#ifndef UMLNODES_H
#define UMLNODES_H

#include "nodes.h"
#include <QDialog>
#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <time.h>


class StickDialog : public QInputDialog {
    Q_OBJECT
public:
    StickDialog(QWidget *parent = 0);

signals:

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *acceptButton;
    QPushButton *closeButton;
};

/*!
 * This concrete class is the StickPerson node.
 * @sa ObjectNode
 */
class StickPerson: public QObject, public ObjectNode {
    Q_OBJECT
public:
    StickPerson();
    BaseNode* clone() { return new StickPerson; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/stickman.png"); }
    QString getText() { return "Stick Person"; }

    void draw(QPainter &painter);
public slots:
    void setName(QString newName) { this->name = newName; }
private:
    QString name;
    //animation vars
        // 0 == punch, 1 == no punch
    bool punchhand;
        time_t start;
        time_t end;
        double dif;


private slots:
//    void setName(QString newName) { name = newName; }
};

class connectionline : public ConnectionNode {


};

class OvalDialog : public QInputDialog {
    Q_OBJECT
public:
    OvalDialog(QWidget *parent = 0);
};

/*!
 * This concrete class is the Oval node.
 * @sa ObjectNode
 */
class OvalNode: public QObject, public ObjectNode {
    Q_OBJECT
public:
    OvalNode();
    BaseNode* clone() { return new OvalNode; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/oval.png"); }
    QString getText() { return "Oval"; }

    void draw(QPainter &painter);
public slots:
    void setName(QString newName) { this->name = newName; }
private:
    int radius;
    QString name;
};

class InteractionLineDialog : public QDialog
{

};

class InteractionLine : public ConnectionNode
{
public:
    BaseNode* clone() { return new InteractionLine; }
    bool hitTest(const QPoint &point) {return false;}
    QDialog* getDialog() { return new InteractionLineDialog; }
    QString getIconPath() { return QString(":/Images/oval.png"); }
    QString getText() { return "InteractionLine"; }
    void draw(QPainter& painter);
};

/* !
 *  This concrete class is the ClassRectangle node.
 *  @sa ObjectNode
 */
/*
class ClassRectangle: public ObjectNode {
private:

public:
    ClassRectangle(QPoint position);
    ~ClassRectangle() {}

    void draw(QPainter &painter);
};
*/

/*
class SquareBoundary: public ObjectNode {
private:

public:
    SquareBoundary(QPoint position);
    ~SquareBoundary() {}

    void draw (QPainter &painter);
};
*/

/*!
 * This concrete class is the Diamond node.
 * @sa ObjectNode
 */
/*
class Diamond: public ObjectNode {
private:

public:
    Diamond(QPoint position);
    ~Diamond() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};
*/

/*!
 * This concrete class is the SimpleLine node.
 * @sa ObjectNode
 */
/*
class SimpleLine: public ConnectionNode {
private:
    int thickness;
public:
    SimpleLine(ObjectNode *point1, ObjectNode *point2);
    ~SimpleLine() {}

    //BaseNode* factory();
    //void test_msg();
    void draw(QPainter &painter);
};
*/

#endif // UMLNODES_H