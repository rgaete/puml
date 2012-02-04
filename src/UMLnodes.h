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


class StickDialog : public QDialog {
    Q_OBJECT
public:
    StickDialog(QWidget *parent = 0);

signals:
    void setName(QString newName);
private slots:

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
class StickPerson: public ObjectNode {
public:
    StickPerson();
    BaseNode* clone() { return new StickPerson; }
    QDialog* getDialog() { return new StickDialog; }
    QString getIconPath() { return QString(":/Images/stickman.png"); }
    QString getText() { return "Stick Person"; }

    void draw(QPainter &painter);
private:
    QString name;

private slots:
//    void setName(QString newName) { name = newName; }
};

class connectionline : public ConnectionNode {


};

class OvalDialog : public QDialog {

};

/*!
 * This concrete class is the Oval node.
 * @sa ObjectNode
 */
class OvalNode: public ObjectNode {
public:
    OvalNode();
    BaseNode* clone() { return new OvalNode; }
    QDialog* getDialog() { return new OvalDialog; }
    QString getIconPath() { return QString(":/Images/oval.png"); }
    QString getText() { return "Oval"; }

    void draw(QPainter &painter);
private:
    int radius;
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
