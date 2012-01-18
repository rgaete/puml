/*  drawarea.cpp
 *
 * --------------------------------------------- */


// FOR USE TO RUN THE OBJECTS SUBJECT TO CHANGE


#include <QtGui>
#include <fstream>
#include <iostream>

#include "drawarea.h"
#include "window.h"
#include "circle.h"
#include "actor.h"

using namespace std;



DrawArea::DrawArea(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}


void DrawArea::paintEvent(QPaintEvent * /* event */)
{
    double xmin = -10;
    double xmax = 10;
    double ymin = -10;
    double ymax = 10;
    double vpxmin = -1;
    double vpxmax = 1;
    double vpymin = -1;
    double vpymax = 1;
    QColor colorval = COLOR;


    QPainter painter(this);
        
    // void QPainter::drawLine ( int x1, int y1, int x2, int y2 );
    // void QPainter::drawText ( int x, int y, const QString & text );
    // void QPainter::setPen();

// This section is for the graphing of the first set of graphs 1 in each quadrant
    Window graph1( xmin, xmax, ymin, ymax, vpxmin, vpxmax, vpymin, vpymax, colorval);


//    Circle obj1(0,0,1, graph1, &painter);
    Actor obj2(0, 0, graph1, &painter);

    // This is the information function. It shows class info
  //  Info();

}


    /*  Event handling  */


void DrawArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height() || width() < image.width() || height() < image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }

    QWidget::resizeEvent(event);
}


void DrawArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

