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
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero(40, 13);

    M(0,0) = 1;
    M(1,0) = 1;
    M(2,0) = 1;
    M(3,0) = 1;

    M(4,1) = 1;
    M(5,1) = 1;
    M(6,1) = 1;
    M(7,1) = 1;

    M(8,2) = 1;
    M(9,2) = 1;
    M(10,2) = 1;
    M(11,2) = 1;

    M(12,3) = 1;
    M(13,3) = 1;
    M(14,3) = 1;
    M(15,3) = 1;

    M(16,4) = 1;
    M(17,4) = 1;
    M(18,4) = 1;
    M(19,4) = 1;

    M(20,5) = 1;
    M(21,5) = 1;
    M(22,5) = 1;
    M(23,5) = 1;

    M(24,6) = 1;
    M(25,6) = 1;
    M(26,6) = 1;
    M(27,6) = 1;

    M(28,7) = 1;
    M(29,7) = 1;
    M(30,7) = 1;
    M(31,7) = 1;

    M(32,8) = 1;
    M(33,8) = 1;
    M(34,8) = 1;
    M(35,8) = 1;

    M(36,9) = 1;
    M(37,9) = 1;
    M(38,9) = 1;
    M(39,9) = 1;

    M(0,10) = 1;
    M(1,11) = 1;
    M(2,12) = 1;

    M(4,10) = 1;
    M(5,11) = 1;
    M(6,12) = 1;

    M(8,10) = 1;
    M(9,11) = 1;
    M(10,12) = 1;

    M(12,10) = 1;
    M(13,11) = 1;
    M(14,12) = 1;

    M(16,10) = 1;
    M(17,11) = 1;
    M(18,12) = 1;

    M(20,10) = 1;
    M(21,11) = 1;
    M(22,12) = 1;

    M(24,10) = 1;
    M(25,11) = 1;
    M(26,12) = 1;

    M(28,10) = 1;
    M(29,11) = 1;
    M(30,12) = 1;

    M(32,10) = 1;
    M(33,11) = 1;
    M(34,12) = 1;

    M(36,10) = 1;
    M(37,11) = 1;
    M(38,12) = 1;

    Eigen::MatrixXd C = Eigen::MatrixXd::Zero(13,3);
    C(10,0) = 1;
    C(11,1) = 1;
    C(12,2) = 1;

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(40,40);

    PartitioningResult p = partitionModel(M, C, I);

    std::cerr << p.X << "\n";
    std::cerr << "\n";
    //std::cerr << p.Z << "\n";
    //std::cerr << "\n";
    double epsilon = std::numeric_limits<double>::epsilon();


    Eigen::MatrixXd Zplus = pseudoInverse(p.Z, epsilon);
    Eigen::MatrixXd Rz = (I - p.Z*Zplus);
    std::cerr << Rz << "\n";
    std::cerr << "\n";
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

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(4,4);

    PartitioningResult p = partitionModel(M, C, I);

}

void TestMatrices::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestMatrices)

#include "testmatrices.moc"
