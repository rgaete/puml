#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(300,300);
}

/** This draws all of the objects that are in the nodes vector
  */
void Canvas::drawList(QPainter &painter)
{
    for (int i=0; i<(int)nodes.size(); i++) {
        nodes[i]->draw(painter);
    }
}

void Canvas::setNewShape(Canvas::ShapeType type)
{
    typeOfNewObject = type;
    whatToDrawNext = Object;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (whatToDrawNext == Object) {
        createObject();
        //drawList();
        update();
        //Here update is better than drawList so that a QPainter
        //can be created by the widget
    }
}

void Canvas::createObject()
{
    if (whatToDrawNext != Object) {
        //we have an error, this function shouldn't be called
        //if we aren't drawing an object
    } else {
        switch (typeOfNewObject) {
        case ShpOval:
            Oval *newShape = new Oval;
            //set the shape's new coordinates
            //Note that the following line pushes back a COPY
            //of the previously created object. To avoid
            //copying, we should use Oval *newShape = new Oval
            //instead
            nodes.push_back(newShape);
            break;
        }
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     drawList(painter);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
}
