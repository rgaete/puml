/*  drawarea.h
 *
 * --------------------------------------------- */

#ifndef DRAWAREA_H
#define DRAWAREA_H

//#define PI 3.14159265   // the value of pi
//#define e 2.71828183    // the value of e, euler's number

#include <QColor>
#include <QImage>
#include <QWidget>
#include <iostream>
using namespace std;

extern int MAX_X;
extern int MAX_Y;
extern  QColor COLOR;
extern int SIZE;
const char classinfo[] = "Zachary Curtis CS 383 Ass 3";


// 940 fits my screen height perfectly

class DrawArea : public QWidget
{
    Q_OBJECT

public:
    DrawArea(QWidget *parent = 0);
    void Info();

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void resizeImage(QImage *image, const QSize &newSize);

    QImage image;

};

#endif
