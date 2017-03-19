#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "permutationtree.h"
#include "binarystring.h"
#include "threecolsarray.h"

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
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Current permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a;
    std::cout << std::endl;
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
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Current permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a;
    std::cout << std::endl;
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
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Current permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a;
    std::cout << std::endl;
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
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Current permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a;
    std::cout << std::endl;
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
    std::cout << "Number of possible shufflings:" << numPermutations << std::endl;
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Current permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a;
    std::cout << std::endl;
}

void testBinaryStringsOperators(int n){
    BinaryString b(n);
    while(b.isIncrementable())
        std::cout << b++ << std::endl;
    std::cout << b << std::endl;
}

void lalgorithmtest(ThreeColsArray& t){
    int iteration_number = 0;
    while(true){
        std::cout << "Iteration " << iteration_number++ << " - array status:" << std::endl;
        std::cout << t << std::endl;
        if(t.isLAlgorithmApplicable())
            t.lalgorithm1iteration();
        else
            break;
    }
    std::cout << "Finished permutations, trying reset" << std::endl;
    t.reset();
    std::cout << t << std::endl;
}

void randomSwappingTest(ThreeColsArray& t, int num_iteration){
    for(int i = 0; i < num_iteration; i++){
        std::cout << "Iteration " << i << " - array status:" << std::endl;
        std::cout << t << std::endl;
        t.randomSwapping();
    }
    std::cout << "Finished permutations, trying reset" << std::endl;
    t.reset();
    std::cout << t << std::endl;
}
