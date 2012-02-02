#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include "nodes.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    enum ShapeType {
        ShpOval,
        ShpStickMan,
        ShpDiamond
    };
    enum DrawingNext {
        Object,
        Connection,
        Nothing
    };
private:
    vector<BaseNode*> nodes;
    ShapeType typeOfNewObject;
    DrawingNext whatToDrawNext;
    QPoint UpperLeft, BottomRight;


public:
    int l, h;

    explicit Canvas(QWidget *parent = 0);
    QSize sizeHint() const;
    void drawList(QPainter &painter);
    void setNewShape(ShapeType type);
    void createObject(QPoint UpperLeft,QPoint BottomRight);
    //void setSelectedObject();
    //void click();
    //void popupMenu();
    //void rightClick();
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // CANVAS_H
