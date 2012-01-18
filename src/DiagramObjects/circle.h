//circle.h

#ifndef CIRCLE_H
#define CIRCLE_H

#include <QtGui>
#include "drawarea.h"
#include "window.h"



class Circle {
 public:
  Circle();
  Circle(double cx, double cy, double r, Window &o, QPainter *p ){
    // init vars
      centerx = cx;
      centery = cy;
      radius = r;
      obj = o;
      painter = p;
      DrawCircle();
  }

//functions
  void DrawCircle();

public:
 // variables
  QPainter *painter;
  double centerx;
  double centery;
  double radius;
  Window obj;

};




#endif // CIRCLE_H
