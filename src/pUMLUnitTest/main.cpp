#include <QtTest/QtTest>
#include "mainwindow_test.h"
#include "nodefactorytest.h"
#include "../mainwindow.h"

int main() {
  MainWindowTest mwt;
  QTest::qExec(&mwt);

  NodeFactoryTest nft;
  QTest::qExec(&nft);

  return 0;
}
