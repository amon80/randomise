#include <QtTest>
#include "myvmp.h"

class TestMyVMP : public QObject
{
    Q_OBJECT
public:
    TestMyVMP();
    ~TestMyVMP();    
private slots:
    void initTestCase();
    void testcase1();
    void cleanUpTestCase();
};

TestMyVMP::TestMyVMP(){

}

TestMyVMP::~TestMyVMP(){

}

void TestMyVMP::testcase1(){
    MyVmp v;
    //They are not the same. Data is fucked up
    v.readvmp("/home/marco/TestData/BetaMapsFillContrast.vmp");
    v.writevmp("/home/marco/TestData/BetaMapsFillContrastCopy.vmp");
}

void TestMyVMP::initTestCase(){

}

void TestMyVMP::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMyVMP)

#include "testmyvmp.moc"
