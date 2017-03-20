#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <vector>
#include "permutationtree.h"
#include "threecolsarray.h"
#include "tests.h"

// Partion the design matrix M basing on the contrast C as indicated on the paper
//X contains the design for the regressors of interest and Z for nuisance variable
//Variables dimensionality:
//M is N x r
//C is r x s
//X is N x s
//Z is N x (r-s)
//with 1 <= s <=r
void partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd& C, Eigen::MatrixXd& X, Eigen::MatrixXd& Z){
   Eigen::MatrixXd D = (M.transpose() * M).inverse();
   Eigen::MatrixXd Ctrasp = C.transpose();

   X = M*D*C*((Ctrasp*D*C).inverse());
   //Cu is a matrix whose columns span in the null space of C
   Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
   Eigen::MatrixXd Cu = lu.kernel();
   Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse());
   Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());
}

/*

//single contrast version
//ask for multi-contrast
template <typename T>
void randomise(T& Y, Eigen::MatrixXd& M, Eigen::MatrixXd& C, bool EE, bool ISE, int J, std::vector<int>b, bool PB){
    Eigen::MatrixXd X(M.rows(), C.cols());
    Eigen::MatrixXd Z(M.rows(), C.rows() - C.cols());

    partitionModel(M, C, X, Z);

    std::vector<std::vector<int>> blocks = findBlocks(b);
    int maxShufflings = calculateMaxShufflings(X, blocks, PB, EE, ISE);
    //TODO
}

*/

int main(int argc, char *argv[])
{
    //First matrix used for tests, no repetitions at all
    Eigen::MatrixXd X1(9, 2);

    X1(0,0) = 1;
    X1(0,1) = 2;
    X1(1,0) = 3;
    X1(1,1) = 4;
    X1(2,0) = 5;
    X1(2,1) = 6;
    X1(3,0) = 7;
    X1(3,1) = 8;
    X1(4,0) = 9;
    X1(4,1) = 10;

    X1(5,0) = 11;
    X1(5,1) = 12;
    X1(6,0) = 13;
    X1(6,1) = 14;
    X1(7,0) = 15;
    X1(7,1) = 16;
    X1(8,0) = 17;
    X1(8,1) = 18;

    //Second matrix used for tests
    Eigen::MatrixXd X2(9, 2);

    X2(0,0) = 1;
    X2(0,1) = 2;
    X2(1,0) = 3;
    X2(1,1) = 4;
    X2(2,0) = 5;
    X2(2,1) = 6;
    X2(3,0) = 7;
    X2(3,1) = 8;
    X2(4,0) = 9;
    X2(4,1) = 10;

    X2(5,0) = 11;
    X2(5,1) = 12;
    X2(6,0) = 1;
    X2(6,1) = 2;
    X2(7,0) = 3;
    X2(7,1) = 4;
    X2(8,0) = 5;
    X2(8,1) = 6;

    std::vector<std::vector<int>> multyRowArray1(3);

    //first row
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    multyRowArray1[0].push_back(1);
    //second row
    multyRowArray1[1].push_back(-1);
    multyRowArray1[1].push_back(-1);
    multyRowArray1[1].push_back(-1);
    multyRowArray1[1].push_back(-2);
    multyRowArray1[1].push_back(-2);
    multyRowArray1[1].push_back(-2);
    multyRowArray1[1].push_back(-3);
    multyRowArray1[1].push_back(-3);
    multyRowArray1[1].push_back(-3);
    //third row
    multyRowArray1[2].push_back(1);
    multyRowArray1[2].push_back(2);
    multyRowArray1[2].push_back(3);
    multyRowArray1[2].push_back(4);
    multyRowArray1[2].push_back(5);
    multyRowArray1[2].push_back(6);
    multyRowArray1[2].push_back(7);
    multyRowArray1[2].push_back(8);
    multyRowArray1[2].push_back(9);


    std::vector<std::vector<int>> multyRowArray2(2);

    //first row
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    multyRowArray2[0].push_back(1);
    //third row
    multyRowArray2[1].push_back(1);
    multyRowArray2[1].push_back(2);
    multyRowArray2[1].push_back(3);
    multyRowArray2[1].push_back(4);
    multyRowArray2[1].push_back(5);
    multyRowArray2[1].push_back(6);
    multyRowArray2[1].push_back(7);
    multyRowArray2[1].push_back(8);
    multyRowArray2[1].push_back(9);


    //testLAlgorithmTree(X1, multyRowArray1);
    //testBinaryCounterTree(X1, multyRowArray1);

    //testRandomSwapping(X1, multyRowArray2, 10);
    //testRandomSignFlipping(X1, multyRowArray2, 10);

    int numrows = 10;

    ThreeColsArray t(numrows);

    for(int i = 0; i < numrows; i++)
        t(0, i) = i;


    int numrandomswappings = 20;
    //lalgorithmtest(t);
    randomSwappingTest(t, numrandomswappings);


    return 0;
}
