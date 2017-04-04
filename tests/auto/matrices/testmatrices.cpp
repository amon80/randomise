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
    void exampleftests();
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

//Example taken from the fsl FEAT user guide
void TestMatrices::exampleftests(){
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(15,3);
    Eigen::MatrixXd C = Eigen::MatrixXd::Zero(3,3);

    C(0,0) = 1;
    C(1,1) = 1;
    C(2,2) = 1;

    for(int i = 0; i < 5; i++)
        M(i, 0) = 1;
    for(int i = 5; i < 10; i++)
        M(i, 1) = 1;
    for(int i = 10; i < 15; i++)
        M(i, 2) = 1;

    PartitioningResult p1 = partitionModel(M, C);

    std::cout << p1 << std::endl;
}


void TestMatrices::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMatrices)

#include "testmatrices.moc"
