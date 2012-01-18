//actor.cpp

#include "actor.h"
#include "window.h"


void Actor::MakeActor()
{
    double radius = 1;
    centery = centery + (2*radius);
    double tempx = centerx;
    double tempy = centery;
    double tempr = radius;
    double blank = 0;
    double bodyx = tempx;
    double bodyy = tempy - tempr;
    double legx = tempx;
    double legy = bodyy - (2*tempr);

    double bodycenterx = (bodyx + legx)/2;
    double bodycentery = (bodyy + legy)/2;
    double leftarmx = bodycenterx - tempr;
    double leftarmy = bodycentery;
    double rightarmx = bodycenterx + tempr;
    double rightarmy = bodycentery;


    double leftfootx = tempx - tempr;
    double leftfooty = legy - (2*tempr);
    double rightfootx = tempx + tempr;
    double rightfooty = legy - (2*tempr);
    QPen *pen;
    painter->setPen(COLOR);

    obj.WindowtoViewPort(tempx, tempy);
    obj.WindowtoViewPort(tempr, blank);
    QPoint point(tempx, tempy);

    obj.WindowtoViewPort(bodyx, bodyy);
    obj.WindowtoViewPort(legx, legy);

    obj.WindowtoViewPort(leftfootx, leftfooty);
    obj.WindowtoViewPort(rightfootx, rightfooty);

    obj.WindowtoViewPort(bodycenterx, bodycentery);
    obj.WindowtoViewPort(leftarmx, leftarmy);
    obj.WindowtoViewPort(rightarmx, rightarmy);

    painter->drawEllipse(point,tempr/11, tempr/11);

    obj.MoveTo2D(bodyx, bodyy);
    obj.DrawTo2D(legx, legy, painter);
    obj.DrawTo2D(leftfootx, leftfooty, painter);
    obj.MoveTo2D(legx, legy);
    obj.DrawTo2D(rightfootx, rightfooty, painter);
    obj.MoveTo2D(bodycenterx, bodycentery);
    obj.DrawTo2D(rightarmx, rightarmy, painter);
    obj.MoveTo2D(bodycenterx, bodycentery);
    obj.DrawTo2D(leftarmx, leftarmy, painter);

}


