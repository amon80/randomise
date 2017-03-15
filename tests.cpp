#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include "permutationtree.h"

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

//Test #2: In particular: example #f from the paper is tried here
//Mixed experiment
void test2(int argc, char *argv[]){
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
    multyRowArray[3].push_back(1);
    multyRowArray[3].push_back(2);
    multyRowArray[3].push_back(3);
    multyRowArray[3].push_back(4);
    multyRowArray[3].push_back(5);
    multyRowArray[3].push_back(6);
    multyRowArray[3].push_back(7);
    multyRowArray[3].push_back(8);
    multyRowArray[3].push_back(9);

    PermutationTree t(multyRowArray);
    std::cout << "finished" << std::endl;
}

//Test #3: Same as test number 2, with simpler configuration
//Example #a -> Within block but not whole block
void test3(int argc, char *argv[]){
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
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);
    multyRowArray[2].push_back(9);

    PermutationTree t(multyRowArray);
    std::cout << "finished" << std::endl;
}

//Test #4: Same as test number 3, with simpler configuration
//Example #b -> Whole block but not within block
void test4(int argc, char *argv[]){
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
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);
    multyRowArray[2].push_back(9);

    PermutationTree t(multyRowArray);
    std::cout << "finished" << std::endl;
}

//Test #5: Same as test number 4, with simpler configuration
//Example #c -> Within block and whole block
void test5(int argc, char *argv[]){
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
    multyRowArray[2].push_back(1);
    multyRowArray[2].push_back(2);
    multyRowArray[2].push_back(3);
    multyRowArray[2].push_back(4);
    multyRowArray[2].push_back(5);
    multyRowArray[2].push_back(6);
    multyRowArray[2].push_back(7);
    multyRowArray[2].push_back(8);
    multyRowArray[2].push_back(9);

    PermutationTree t(multyRowArray);
    std::cout << "finished" << std::endl;
}

//Test #6: Same as test number 5, with simpler configuration
//Example #f -> unrestricted exchangeability
void test6(int argc, char *argv[]){
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
    multyRowArray[1].push_back(1);
    multyRowArray[1].push_back(2);
    multyRowArray[1].push_back(3);
    multyRowArray[1].push_back(4);
    multyRowArray[1].push_back(5);
    multyRowArray[1].push_back(6);
    multyRowArray[1].push_back(7);
    multyRowArray[1].push_back(8);
    multyRowArray[1].push_back(9);

    PermutationTree t(multyRowArray);
    std::cout << "finished" << std::endl;
}
