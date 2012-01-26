#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <QMenu>
#include "nodes.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    enum ShapeType {
        ShpOval,
        ShpStickMan,
        ShpDiamond,
        ShpClassRectangle,
        ShpSquare
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
    int indexOfSelectedObject;      //This is the index of the
                                    //selected object in nodes.
                                    //-1 signifies nothing selected.
    QMenu *menuPopup;
    QAction *actionDelete;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;

    void determineSelectedObject(int x, int y);
    void drawList(QPainter &painter);
    void createObject(QPoint position);
public:
    explicit Canvas(QWidget *parent = 0);
    QSize sizeHint() const;
    void setNewShape(ShapeType type);
    void setMode(DrawingNext mode);

    //void setSelectedObject();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

signals:

public slots:
    void on_actionDelete_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
};

#endif // CANVAS_H
