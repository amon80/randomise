#include <QtTest>
#include "../../../src/binarystring.h"

class TestBinaryCounter : public QObject
{
    Q_OBJECT

public:
    TestBinaryCounter();
    ~TestBinaryCounter();

private:
    BinaryString b;
    BinaryString bplus1;
    BinaryString invalid;
    BinaryString null;

private slots:
    void initTestCase();
    void test_case1();
    void test_case2();
    void cleanUpTestCase();
};

TestBinaryCounter::TestBinaryCounter()
    :b(BinaryString(5)),
     bplus1(BinaryString(5, 1)),
     invalid(BinaryString(0,4)),
     null(BinaryString())
{

}

TestBinaryCounter::~TestBinaryCounter()
{

}



void TestBinaryCounter::initTestCase(){

}

void TestBinaryCounter::test_case1()
{
    BinaryString c(b);
    QCOMPARE(false, bplus1 < bplus1);
    QCOMPARE(true, c < bplus1);
    QCOMPARE(true, ++c == bplus1);
}

void TestBinaryCounter::test_case2(){
    BinaryString c(b);
    QCOMPARE(c, b);
    std::cout << c << std::endl;
    while(c.isIncrementable()){
        std::cout << ++c << std::endl;
    }
    int nbits = c.size();
    for(int i = 0; i < nbits; i++){
        int current_bit = c[i];
        QCOMPARE(current_bit, 1);
    }
}

void TestBinaryCounter::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestBinaryCounter)

#include "testbinarycounter.moc"
