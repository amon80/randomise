#include <QtTest>
#include <iostream>
#include "matrices.h"

class TestMatrices : public QObject
{
    Q_OBJECT

public:
    TestMatrices();
    ~TestMatrices();

private slots:
    void initTestCase();
    void partitionModelTestCase1();
    void partitionModelTestCase2();
    void partitionModelTestCase3();
    void partitionModelTestCase4();
    void partitionModelTestCase5();
    void example5noNuisance();
    void cleanUpTestCase();
};

TestMatrices::TestMatrices()
{

}

TestMatrices::~TestMatrices()
{

}



void TestMatrices::initTestCase(){

}

//No nuisance, one sample Ttest
//TODO
void TestMatrices::partitionModelTestCase1(){

}

//No nuisance, two sample unpaired Ttest
//TODO
void TestMatrices::partitionModelTestCase2(){

}

//Nuisance, two sample unpaired Ttest
//TODO
void TestMatrices::partitionModelTestCase3(){

}

//Nuisance, two sample unpaired Ttest
//TODO
void TestMatrices::partitionModelTestCase4(){

}

//wo-Sample Paired T-test (Paired Two-Group Difference)
void TestMatrices::partitionModelTestCase5(){

}

void TestMatrices::example5noNuisance(){
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(4,2);

    M(0,0) = 1;
    M(1,0) = 1;
    M(2,1) = 1;
    M(3,1) = 1;

    Eigen::MatrixXd C(2,1);

    C(0,0) = 1;
    C(1,0) = -1;

    PartitioningResult p = partitionModel(M, C);

}


void TestMatrices::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMatrices)

#include "testmatrices.moc"
