#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "permutationtree.h"
#include "binarystring.h"

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

//Test #2: In particular: example #e from the paper is tried here
//Mixed experiment
void test2(Eigen::MatrixXd& X){
    std::vector<std::vector<int>> multyRowArray(4);

    //first row
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    //second row
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    //third row
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    //fourth row
    multyRowArray[3].push_back(0);
    multyRowArray[3].push_back(1);
    multyRowArray[3].push_back(2);
    multyRowArray[3].push_back(3);
    multyRowArray[3].push_back(4);
    multyRowArray[3].push_back(5);
    multyRowArray[3].push_back(6);
    multyRowArray[3].push_back(7);
    multyRowArray[3].push_back(8);

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << numPermutations << std::endl;
}

//Test #3: Same as test number 2, with simpler configuration
//Example #a -> Within block but not whole block
void test3(Eigen::MatrixXd& X){
    std::vector<std::vector<int>> multyRowArray(3);

    //first row
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    multyRowArray[0].push_back(-1);
    //second row
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    //third row
    multyRowArray[2].push_back(0);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << numPermutations << std::endl;
}

//Test #4: Same as test number 3, with simpler configuration
//Example #b -> Whole block but not within block
void test4(Eigen::MatrixXd& X){
    std::vector<std::vector<int>> multyRowArray(3);

    //first row
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    //second row
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-1);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(-2);
    multyRowArray[1].push_back(-3);
    multyRowArray[1].push_back(-3);
    multyRowArray[1].push_back(-3);
    //third row
    multyRowArray[2].push_back(0);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << numPermutations << std::endl;
}

//Test #5: Same as test number 4, with simpler configuration
//Example #c -> Within block and whole block
void test5(Eigen::MatrixXd& X){
    std::vector<std::vector<int>> multyRowArray(3);

    //first row
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    //second row
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(3);
    //third row
    multyRowArray[2].push_back(0);
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << numPermutations << std::endl;
}

//Test #6: Same as test number 5, with simpler configuration
//Example #f -> unrestricted exchangeability
void test6(Eigen::MatrixXd& X){
    std::vector<std::vector<int>> multyRowArray(2);

    //first row
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    multyRowArray[0].push_back(1);
    //second row
    multyRowArray[1].push_back(0);
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(4);
    multyRowArray[1].push_back(5);
    multyRowArray[1].push_back(6);
    multyRowArray[1].push_back(7);
    multyRowArray[1].push_back(8);

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << numPermutations << std::endl;
}

void testBinaryStringsOperators(){
    BinaryString b1(8);

    do{
        std::cout << b1 << std::endl;
    }while(b1++ != b1);
}
