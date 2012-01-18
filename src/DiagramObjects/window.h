#ifndef WINDOW_H
#define WINDOW_H


#include <QtGui>
#include "drawarea.h"



class Window {
 public:
  Window(){}
  Window(double x1, double x2, double y1, double y2, double vx1, double vx2, double vy1, double vy2, QColor colorval ){
    xmin = x1;
    xmax = x2;
    ymin = y1;
    ymax = y2;
    vxmin = vx1;
    vxmax = vx2;
    vymin = vy1;
    vymax = vy2;
    setcolor = colorval;
    size = SIZE;
  }

  void MoveTo2D( double x, double y );
  void DrawTo2D( double x, double y, QPainter* painter );
  void WindowtoViewPort(double &x, double &y);
  void SetWindow(double x1, double x2, double y1, double y2);
  void SetViewPort(double x1, double x2, double y1, double y2);


public:
  double xmin;
  double xmax;
  double ymin;
  double ymax;



  double vxmin;
  double vxmax;
  double vymin;
  double vymax;

  double last_x;
  double last_y;

  QColor setcolor;
  int size;
};

#endif // WINDOW_H
