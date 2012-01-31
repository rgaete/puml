#include <QtGui/QApplication>
#include <QMessageBox>
#include "mainwindow.h"

/*
class MyApplication : public QApplication {
public:
  MyApplication(int& argc, char ** argv) :
    QApplication(argc, argv) { }
  virtual ~MyApplication() { }

  // reimplemented from QApplication so we can throw exceptions in slots
  virtual bool notify(QObject * receiver, QEvent * event) {
    try {
      return QApplication::notify(receiver, event);
    } catch(std::exception& e) {
          QMessageBox::critical(0, QString("pUML"), QString(e.what()), QMessageBox::Ok);
      //qCritical() << "Exception thrown:" << e.what();
    }
    return false;
  }
};
*/
/*!
 * @param argc
 * @param *argv
 */
int main(int argc, char *argv[])
{
    //MyApplication a(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
