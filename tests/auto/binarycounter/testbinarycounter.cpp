#include <QtTest>
#include "binarystring.h"

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
    void comparetestcase();
    void incrementtestcase();
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

void TestBinaryCounter::comparetestcase()
{
    BinaryString c(b);
    QCOMPARE(false, bplus1 < bplus1);
    QCOMPARE(true, c < bplus1);
    QCOMPARE(true, ++c == bplus1);
}

void TestBinaryCounter::incrementtestcase(){
    BinaryString c(b);
    //testing copy constructor
    QCOMPARE(c, b);
    std::cout << c << std::endl;
    int nbits = c.size();
    int expected_increments = 1;
    expected_increments <<= nbits;
    int actual_increments_performed = 1;
    while(c.isIncrementable()){
        actual_increments_performed++;
        std::cout << ++c << std::endl;
    }
    QCOMPARE(expected_increments, actual_increments_performed);
    for(int i = 0; i < nbits; i++){
        QCOMPARE(c[i], 1);
    }
    c.reset();
    for(int i = 0; i < nbits; i++){
        QCOMPARE(c[i], 0);
    }
}

void TestBinaryCounter::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestBinaryCounter)

#include "testbinarycounter.moc"
