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
    void testcase3();
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
    //v.readvmp("/home/marco/TestData/TMapFillContrast.vmp");
    //v.writevmp("/home/marco/TestData/TMapFillContrastCopy.vmp");
}

void TestMyVMP::testcase3(){
    MyVmp v;
    v.addSubMap();
    v.getSubHeader(0).NameOfMap = "Contrast " + std::to_string(1);
    v.getSubHeader(0).ThreshMin = 0;
    v.getSubHeader(0).ThreshMax = 10;
    v.getSubHeader(0).df1 = 0;
    v.getSubHeader(0).MapType = t;
    v.getSubHeader(0).ClusterSize = 0;
    v.getSubHeader(0).UseClusterSize = 0;
    //v.getSubHeader(0).NrOfStatVoxels = ???;
    int dimX = v.getDimX();
    int dimY = v.getDimY();
    int dimZ = v.getDimZ();
    int dim = dimX * dimY * dimZ;
    for(int j = 0; j < dim; j++){
        v[0][j] = 0;
    }
    v.writevmp("/home/marco/TestData/example.vmp");
}


void TestMyVMP::initTestCase(){

}

void TestMyVMP::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMyVMP)

#include "testmyvmp.moc"
