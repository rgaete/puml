#include <QtTest/QtTest>
#include "nodefactorytest.h"

int main() {
    NodeFactoryTest nft;
    QTest::qExec(&nft);

    return 0;
}
