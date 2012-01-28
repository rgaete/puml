#include <QtGui/QApplication>
#include "mainwindow.h"

/*!
 * @param argc
 * @param *argv
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
