#include "window.h"
#include <iostream>
using namespace std;

void Window::MoveTo2D(double x, double y)
{
    // MoveTo2D function, sets the "pen" to a specified location
    last_x = x;
    last_y = y;
}

void Window::DrawTo2D(double x, double y, QPainter *painter)
{
    //DrawTo2D function, moves the "pen" to a location drawing a line
    painter->drawLine(last_x,last_y, x, y);
    last_x = x;
    last_y = y;
}

void Window::WindowtoViewPort(double &x, double &y)
{
    double viewx;
    double viewy;
    double worldx;
    double worldy;

    // double transformation from world to viewport to screen

    viewx = ((x - xmin)/(xmax - xmin))*(vxmax - vxmin) + vxmin;
    viewy = ((y - ymin)/(ymax - ymin))*(vymax - vymin) + vymin;
    //converts from window coords to viewport coords
        worldx = (viewx * (MAX_X/2))+(MAX_X/2);
        worldy = (viewy * (-1 * MAX_Y/2))+(MAX_Y/2);
        // converts from veiwport coords to device pixels

    x = worldx;
    y = worldy;
}

void Window::SetWindow(double x1, double x2, double y1, double y2)
{
    // Sets up the variables used for window settings
    xmin = x1;
    xmax = x2;
    ymin = y1;
    ymax = y2;

}


void Window::SetViewPort(double x1, double x2, double y1, double y2)
{
    // Sets up the variables used for viewport settings
    vxmin = x1;
    vxmax = x2;
    vymin = y1;
    vymax = y2;

}

