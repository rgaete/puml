#include "../mainwindow.h"
#include "./mainwindow_test.h"

MainWindowTest::MainWindowTest(QObject *parent)
               :QObject(parent) {
}

/*! Initializes this unit test
*/
void MainWindowTest::initTestCase() {
  //this->app = new QApplication(0, NULL);
  //this->app->setStyleSheet("QToolButton { min-width: 150px }");

  /*
  MainWindow w;
  w.show();

  act = QAction("test", w);

  this->app->exec();
  */
}

/*! Tests the registerPrototype function.
*/
void MainWindowTest::testRegister() {

}

/*! Cleans up this unit test
*/
void MainWindowTest::cleanupTestCase() {
  this->app->exit();
}
