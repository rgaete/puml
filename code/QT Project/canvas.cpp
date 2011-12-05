#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    //Set the size policy to say that sizeHint() is a recomended
    //minimum, but the widget should take up all space available,
    //and the widget can also be smaller than the sizeHint().
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Set the background to white. This is done by setting the
    //background role of a new palette to white, and then setting
    //that palette to this widget. This way the background color
    //is painted before the paintevent is called
    setAutoFillBackground(true);
    QPalette newPalette(palette());
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);

    //Initialize typeOfNewObject
    whatToDrawNext = Nothing;
}

/* sizeHint: returns a recomended size, used by layouts. */
QSize Canvas::sizeHint() const
{
    return QSize(50,50);
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
        createObject(event->pos());
        //drawList();
        update();
        //Here update is better than drawList so that a QPainter
        //can be created by the widget
    }
}

void Canvas::createObject(const QPoint &where)
{
    if (whatToDrawNext != Object) {
        //we have an error, this function shouldn't be called
        //if we aren't drawing an object
    } else {
        ObjectNode *newShape;
        //create whatever shape we need
        switch (typeOfNewObject) {
        case ShpOval:
            newShape = new Oval(where);
            break;
        case ShpDiamond:
            newShape = new Diamond(where);
            break;
        }

        //add the node to the vector
        nodes.push_back(newShape);
    }
}

void Canvas::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);

     /* Draw a grid. Shamelessly stolen from a previous
      * assignment. */
     int lineThickness = 1;
     QColor lineColor = QColor("black");
     int colWidth = 50;
     int rowHeight = 50;
     //set up the pen using the preferences
     QPen pen;
     pen.setWidth(lineThickness);
     pen.setColor(lineColor);
     pen.setStyle(Qt::DotLine);
     painter.setPen(pen);

     //Create two vectors of lines, then use drawLines
     //to draw them
     QVector<QLine> hlines;
     QVector<QLine> vlines;
     int vlinescount = width()/colWidth + 1;
     int hlinescount = height()/rowHeight + 1;
     for (int i=0; i<vlinescount; i++) {
         vlines.push_back(QLine(i*colWidth, 0, i*colWidth, hlinescount*rowHeight));
     }
     for (int i=0; i<hlinescount; i++) {
         hlines.push_back(QLine(0, i*rowHeight, vlinescount*colWidth, i*rowHeight));
     }
     painter.drawLines(hlines);
     painter.drawLines(vlines);

     //Draw the nodes!!!
     drawList(painter);

     //Kill the painter
     painter.end();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{

}
