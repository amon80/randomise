#include <QtTest>
#include <iostream>
#include "matrices.h"

class TestMatrices : public QObject
{
    Q_OBJECT

public:
    TestMatrices();
    ~TestMatrices();

private:
    Eigen::MatrixXd M1;
    Eigen::MatrixXd C1;
    Eigen::MatrixXd C2;

private slots:
    void initTestCase();
    void partitionModelTestCase1();
    void cleanUpTestCase();
};

TestMatrices::TestMatrices()
    : M1(Eigen::MatrixXd (3, 2)),
      C1(Eigen::MatrixXd (2, 1)),
      C2(Eigen::MatrixXd (1, 1))
{
    for(int i = 0; i < 3; i++){
        M1(i,0) = 1;
    }
    for(int i = 0; i < 3; i++){
        M1(i,1) = i+10;
    }

    C1(0,0) = 1;
    C1(1,0) = 0;

    C2(0,0) = 1;
}

TestMatrices::~TestMatrices()
{

}



void TestMatrices::initTestCase(){

}

void TestMatrices::partitionModelTestCase1(){
    PartitioningResult result = partitionModel(M1, C1);
    std::cout << result.X << std::endl;
    std::cout << result.Z << std::endl;
}

void TestMatrices::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMatrices)

#include "testmatrices.moc"
