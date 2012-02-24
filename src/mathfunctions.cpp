#include "mathfunctions.h"

//Still need to review for arctan singularity. Could cause crash.

double mathfunctions::computeAngle(QPoint p1, QPoint p2)
{
    double angle=0;
    double opposite=p1.y()-p2.y();
    double adjacent=p2.x()-p1.x();
    if(opposite<0)
    {
        angle+=PI;
    }
    else if(adjacent<0)
    {
        angle+=PI;
    }
    if(opposite<0 && adjacent>0)
    {
        angle+=PI;
    }
    return angle+(atan(opposite/adjacent));
}

double mathfunctions::normalize(QPoint p1, QPoint p2)
{
    return pow((pow((double)p2.x()-p1.x(), 2)+pow((double)p2.y()-p1.y(), 2)),0.5);
}

double mathfunctions::toRadians(double angle)
{
    return angle*180.0/PI;
}
