#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
#include <QRect>
#include "math.h"
#define PI 3.14159

namespace mathfunctions
{
    double computeAngle(QPoint p1, QPoint p2);
    double normalize(QPoint p1, QPoint p2);
}

#endif // MATHFUNCTIONS_H

