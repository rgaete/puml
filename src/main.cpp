#include <QtGui/QApplication>
#include "actorDialog.h"
#include "mainwindow.h"

/*!
 * @param argc
 * @param *argv
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ActorDialog *dialog = new ActorDialog;
    dialog->show();
    w.show();

    return a.exec();
}
