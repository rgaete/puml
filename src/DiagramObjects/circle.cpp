//circle.cpp

#include "circle.h"
#include "window.h"


void Circle::DrawCircle()
{
    double tempx = centerx;
    double tempy = centery;
    double tempr = radius;
    double blank = 0;

    painter->setPen(COLOR);
    obj.WindowtoViewPort(tempx, tempy);
    obj.WindowtoViewPort(tempr, blank);
    QPoint point(tempx, tempy);

    painter->drawEllipse(point,tempr, tempr);


}

