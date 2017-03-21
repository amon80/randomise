#include <iostream>
#include "permutationtree.h"
#include "binarystring.h"
#include "threecolsarray.h"
#include "matrices.h"
#include <set>
#include <string>

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

//NOTE: this only works when the permutation is made up of all numbers with
//1 digit
std::string createStringFromVector(std::vector<int>& permutation){
    std::string toReturn;
    for(int a: permutation)
        toReturn.append(std::to_string(a));
    return toReturn;
}

void testLAlgorithmTree(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray) {

    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, true, false);
    std::cout << "Number of possible shufflings:" << numPermutations << std::endl;
    int currentPermutation = 1;
    std::set<std::string> generatedPermutations;
    while(true){
        //std::vector<int> currentPerm = t.getPermutationVector();
        std::vector<int> currentPerm = t.getSignVector();
        std::string currentPermString = createStringFromVector(currentPerm);
        if(generatedPermutations.count(currentPermString))
            std::cout << "Warning! " << currentPermString << " already generated!" << std::endl;
        else
            generatedPermutations.insert(currentPermString);
        Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
        std::cout << currentPermutation << " permutation vector is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        std::cout << currentPermutation++ << " permutation matrix is: " << std::endl;
        std::cout << P << std::endl;
        if(!t.LAlgorithm())
            break;
    }

    std::cout << "Finished permutations! Restoring the tree to its original state" << std::endl;
    t.resetTreePermutationState();
    //std::vector<int> currentPerm = t.getPermutationVector();
    std::vector<int> currentPerm = t.getSignVector();
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
        Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
        std::cout << currentPermutation << " sign flipping vector is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        std::cout << currentPermutation++ << " sign flipping matrix is: " << std::endl;
        std::cout << P << std::endl;
        if(!t.signFlipping())
            break;
    }

    std::cout << "Finished sign flippings! Restoring the tree to its original state" << std::endl;
    t.resetTreeSignState();
    std::vector<int> currentPerm = t.getSignVector();
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
    std::cout << "Iteration 0 - array status:" << std::endl;
    std::cout << t << std::endl;
    for(int i = 1; i <= num_iteration; i++){
        t.randomSwapping();
        std::cout << "Iteration " << i << " - array status:" << std::endl;
        std::cout << t << std::endl;
    }
    std::cout << "Finished permutations, trying reset" << std::endl;
    t.reset();
    std::cout << t << std::endl;
}

void testRandomSwapping(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray, int n){
    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, true, false);
    std::cout << "Number of possible permutations:" << numPermutations << std::endl;
    std::vector<int> originalPerm = t.getSignVector();
    Eigen::MatrixXd O = buildShufflingMatrix(originalPerm);
    std::cout << " Original permutation is: " << std::endl;
    for(int a: originalPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Original shuffling matrix is: " << std::endl;
    std::cout << O << std::endl;
    std::cout << std::endl;
    for(int currentPermutation = 1; currentPermutation <= n; currentPermutation++){
        t.randomShuffle();
        std::vector<int> currentPerm = t.getSignVector();
        Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
        std::cout << currentPermutation << " Shuffling vector is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        std::cout << currentPermutation << " shuffling matrix is: " << std::endl;
        std::cout << P << std::endl;
    }

    std::cout << "Finished required random shufflings! Restoring the tree to its original state" << std::endl;
    t.resetTreePermutationState();
    std::vector<int> currentPerm = t.getSignVector();
    std::cout << "Original permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;
}

void testRandomSignFlipping(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray, int n){
    PermutationTree t(multyRowArray);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, false, true);
    std::cout << "Number of possible sign flippings:" << numPermutations << std::endl;
    for(int currentPermutation = 1; currentPermutation <= n; currentPermutation++){
        std::vector<int> currentPerm = t.getSignVector();
        Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
        std::cout << currentPermutation << " sign flipping vector is: " << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        std::cout << currentPermutation << " sign flipping matrix is: " << std::endl;
        std::cout << P << std::endl;
        t.randomSignFlip();
    }

    std::cout << "Finished required random sign flippings! Restoring the tree to its original state" << std::endl;
    t.resetTreeSignState();
    std::vector<int> currentPerm = t.getSignVector();
    std::cout << "Original permutation is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;
}

