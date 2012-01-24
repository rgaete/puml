#include "canvas.h"

/*! Constructor for the canvas. It sets the sizing policy,
  sets the background to white, and sets the
  whatToDrawNext variable to Nothing.
  */
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

/*! sizeHint: returns a recomended size, used by layouts. */
QSize Canvas::sizeHint() const
{
    return QSize(50,50);
}

/*! This draws all of the objects that are in the nodes vector
    by calling their draw functions.
  */
void Canvas::drawList(QPainter &painter)
{
    for (int i=0; i<(int)nodes.size(); i++) {
        nodes[i]->draw(painter);
    }
}

/*! This function is called when you want to set
    what the canvas is going to draw next.
 */
void Canvas::setNewShape(Canvas::ShapeType type)
{
    typeOfNewObject = type;
    whatToDrawNext = Object;
}

/*! This function will do various things based on
    what whatToDrawNext is set to. It can create
    objects and connections, select objects, etc.
*/
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (whatToDrawNext == Object) {
        createObject(event->pos());
        //Call to update to initiate a paintEvent
        update();
    }
}

/*! This function is used to create a new object at a
    certain position. It will create a new object
    based on what typeOfNewObject is.
*/
void Canvas::createObject(QPoint position)
{
    if (whatToDrawNext != Object) {
        //we have an error, this function shouldn't be called
        //if we aren't drawing an object
    } else {
        ObjectNode *newShape;
        //create whatever shape we need
        switch (typeOfNewObject) {
        case ShpOval:
            newShape = new Oval(position);
            break;
        case ShpDiamond:
            newShape = new Diamond(position);
            break;
        case ShpStickMan:
            newShape = new StickPerson(position);
            break;
        case ShpClassRectangle:
            newShape = new ClassRectangle(position);
            break;
        }

        //add the node to the vector
        nodes.push_back(newShape);
    }
}

/*! This function paints the canvas. That means it
    draws the background grid and then calls drawList.
*/
void Canvas::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);

     /* Draw a grid. Shamelessly stolen from a previous
      * assignment. */
     int lineThickness = 1;
     QColor lineColor = QColor(245,245,245,255);
     int colWidth = 10;
     int rowHeight = 10;
     //set up the pen using the preferences
     QPen pen;
     pen.setWidth(lineThickness);
     pen.setColor(lineColor);
//     pen.setStyle(Qt::DotLine);
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

//These functions aren't used yet.

void Canvas::mousePressEvent(QMouseEvent *event)
{
    //UpperLeft.setX(event->x());
    //UpperLeft.setY(event->y());
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    //BottomRight.setX(event->x());
    //BottomRight.setY(event->y());
}


