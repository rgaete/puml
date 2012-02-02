#ifndef ACTOR_H
#define ACTOR_H


#include <QtGui>
#include "drawarea.h"
#include "window.h"



class Actor {
 public:
  Actor();
  Actor(double cx, double cy, Window &o, QPainter *p ){
    // init vars
      centerx = cx;
      centery = cy;
     // radius = r;
      obj = o;
      painter = p;
      MakeActor();
  }

//functions
  void MakeActor();

public:
 // variables
  QPainter *painter;
  double centerx;
  double centery;
 // double radius;
  Window obj;

};




#endif // ACTOR_H
