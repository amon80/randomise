#include "binarystring.h"
#include<QtTest/QtTest>

class BinaryCounterTester : public QObject
{
    Q_OBJECT
private slots:
    void incrementTest();
};

void BinaryCounterTester::incrementTest(){
    BinaryString b1(10, 1);

    BinaryString b2(10, 2);

    QVERIFY(++b1 == b2);
}

QTEST_MAIN(BinaryCounterTester)
#include "binarycountertester.moc"
