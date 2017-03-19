#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include "permutationtree.h"
#include "binarystring.h"
#include "threecolsarray.h"

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

void testLAlgorithmTree(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray) {

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, true, false);
    std::cout << "Number of possible shufflings:" << numPermutations << std::endl;
    int currentPermutation = 1;
    while(true){
        std::vector<int> currentPerm = t.getPermutationVector();
        std::cout << currentPermutation++ << " permutation is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        if(!t.LAlgorithm())
            break;
    }

    std::cout << "Finished permutations! Restoring the tree to its original state" << std::endl;
    t.resetTreePermutationState();
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Original permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;
}

void testBinaryCounterTree(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray) {

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, false, true);
    std::cout << "Number of possible sign flipping:" << numPermutations << std::endl;
    int currentPermutation = 1;
    while(true){
        std::vector<int> currentPerm = t.getSignVector();
        std::cout << currentPermutation++ << " sign flipping is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        if(!t.signFlipping())
            break;
    }

    std::cout << "Finished sign flippings! Restoring the tree to its original state" << std::endl;
    t.resetTreeSignState();
    std::vector<int> currentPerm = t.getPermutationVector();
    std::cout << "Original sign flipping is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;

}

void testBinaryStringsOperators(int n){
    BinaryString b(n);
    std::cout << b << std::endl;
    while(b.isIncrementable())
        std::cout << ++b << std::endl;
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
