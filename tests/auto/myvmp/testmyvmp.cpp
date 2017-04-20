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
    void testcase2();
    void cleanUpTestCase();
};

TestMyVMP::TestMyVMP(){

}

TestMyVMP::~TestMyVMP(){

}

//Check if they're the same
void TestMyVMP::testcase1(){
    MyVmp v;
    v.readvmp("/home/marco/TestData/BetaMapsFillContrast.vmp");
    v.writevmp("/home/marco/TestData/BetaMapsFillContrastCopy.vmp");
}

//Check if they're the same
void TestMyVMP::testcase2(){
    MyVmp v;
    v.readvmp("/home/marco/TestData/TMapFillContrast.vmp");
    v.writevmp("/home/marco/TestData/TMapFillContrastCopy.vmp");
}


void TestMyVMP::initTestCase(){

}

void TestMyVMP::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMyVMP)

#include "testmyvmp.moc"
