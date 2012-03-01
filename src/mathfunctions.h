// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_MATHFUNCTIONS_H_
#define SRC_MATHFUNCTIONS_H_
#include <QRect>
#include "./math.h"

#define PI 3.14159

namespace mathfunctions {
  double computeAngle(QPoint p1, QPoint p2);
  double calculateHypot(QPoint p1, QPoint p2);
  double toDegrees(double radians);
}

#endif  // SRC_MATHFUNCTIONS_H_
