#include <QtTest>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include "permutationtree.h"
#include "multyrowarray.h"
#include "matrices.h"

//Utility class used to compare generated permutations
struct classcomp {
    //assuming that lhs and rhs have the same size
    bool operator() (const std::vector<int>& lhs, const std::vector<int>& rhs) const{
        int n = lhs.size();

        for(int i = 0; i < n; i++){
            if(lhs[i] < rhs[i])
                return true;
            else if(lhs[i] > rhs[i])
                return false;
        }
        return false;
    }
};

class TestPermutationTree : public QObject
{
    Q_OBJECT

public:
    TestPermutationTree();
    ~TestPermutationTree();

private:
    Eigen::MatrixXd X1;
    Eigen::MatrixXd X2;
    MultyRowArray a1;
    MultyRowArray a2;
    void testLAlgorithmTree(Eigen::MatrixXd& X, MultyRowArray& a);
    void testAllSignFlippingsTree(Eigen::MatrixXd& X, MultyRowArray& a);
    void testAllSignFlippingsAndPermutation(Eigen::MatrixXd& X, MultyRowArray& a);
    void testRandomSwapping(Eigen::MatrixXd& X, MultyRowArray& a, int n);
    void testRandomSignFlipping(Eigen::MatrixXd& X, MultyRowArray& a, int n);
    void computeShuffling(PermutationTree &t, std::set<std::vector<int>, classcomp> &generatedPermutations, int &currentPermutation);

private slots:
    void initTestCase();
    void allSignFlippingsAndPermutationsTest1();
    void allSignFlippingsAndPermutationsTest2();
    //Binary Flippings only need two tests since they don't care about
    //repetitions in the design matrix
    void allSignFlippingsTest1();
    void allSignFlippingsTest2();
    void lAlgorithmtest1();
    void lAlgorithmtest2();
    void lAlgorithmtest3();
    void lAlgorithmtest4();
    void cleanUpTestCase();
};

//--------------PRIVATE METHODS------------------

void TestPermutationTree::testLAlgorithmTree(Eigen::MatrixXd& X, MultyRowArray& a) {

    PermutationTree t(a);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, true, false);
    std::cout << "Number of possible shufflings:" << numPermutations << std::endl;
    int currentPermutation = 0;
    std::set<std::vector<int>, classcomp> generatedPermutations;
    t.reverseLAlgorithm();
    while(true){
        //std::vector<int> currentPerm = t.getPermutationVector();
        std::vector<int> currentPerm = t.getSignVector();
        if(generatedPermutations.count(currentPerm)){
            std::cout << "Warning! Permutation:" << std::endl;
            for(int a: currentPerm)
                std::cout << a << " ";
            std::cout << std::endl;
            std::cout << " already generated!" << std::endl;
            //the test fails if we generate twice the same permutation
            QCOMPARE(false, true);
        }
        else
            generatedPermutations.insert(currentPerm);
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
    QCOMPARE(currentPermutation, numPermutations);

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

void TestPermutationTree::testAllSignFlippingsTree(Eigen::MatrixXd& X, MultyRowArray& a) {

    PermutationTree t(a);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, false, true);
    std::cout << "Number of possible sign flipping:" << numPermutations << std::endl;
    int currentPermutation = 0;
    std::set<std::vector<int>, classcomp> generatedPermutations;
    while(true){
        //std::vector<int> currentPerm = t.getPermutationVector();
        std::vector<int> currentPerm = t.getSignVector();
        if(generatedPermutations.count(currentPerm)){
            std::cout << "Warning! Sign flipping:" << std::endl;
            for(int a: currentPerm)
                std::cout << a << " ";
            std::cout << std::endl;
            std::cout << " already generated!" << std::endl;
            //the test fails if we generate twice the same permutation
            QCOMPARE(false, true);
        }
        else
            generatedPermutations.insert(currentPerm);
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
    QCOMPARE(currentPermutation, numPermutations);
    std::cout << "Finished sign flippings! Restoring the tree to its original state" << std::endl;
    t.resetTreeSignState();
    std::vector<int> currentPerm = t.getSignVector();
    std::cout << "Original sign flipping is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;

}

void TestPermutationTree::computeShuffling(PermutationTree& t, std::set<std::vector<int>, classcomp>& generatedPermutations, int& currentPermutation)
{
    std::vector<int> currentPerm = t.getSignVector();
    if(generatedPermutations.count(currentPerm)){
        std::cout << "Warning! Shuffling:" << std::endl;
        for(int a: currentPerm)
            std::cout << a << " ";
        std::cout << std::endl;
        std::cout << " already generated!" << std::endl;
        //the test fails if we generate twice the same permutation
        QCOMPARE(false, true);
    }
    else
        generatedPermutations.insert(currentPerm);
    Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
    std::cout << currentPermutation << " shuffling is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << currentPermutation++ << " shuffling matrix is: " << std::endl;
    std::cout << P << std::endl;
}

void TestPermutationTree::testAllSignFlippingsAndPermutation(Eigen::MatrixXd& X, MultyRowArray &a){
    PermutationTree t(a);
    t.initializeThreeColsArray();
    t.initializeBinaryCounters();
    int numPermutations = t.calculatePermutations(X, true, true);
    std::cout << "Number of possible shufflings:" << numPermutations << std::endl;
    int currentPermutation = 0;
    std::set<std::vector<int>, classcomp> generatedPermutations;
    t.reverseLAlgorithm();
    computeShuffling(t, generatedPermutations, currentPermutation);
    while(t.signFlipping()){
        computeShuffling(t, generatedPermutations, currentPermutation);
    }
    t.resetTreeSignState();
    while(t.LAlgorithm()){
        t.resetTreeSignState();
        computeShuffling(t, generatedPermutations, currentPermutation);
        while(t.signFlipping()){
            computeShuffling(t, generatedPermutations, currentPermutation);
        }
    }
    QCOMPARE(currentPermutation, numPermutations);
    std::cout << "Finished all shufflings! Restoring the tree to its original state" << std::endl;
    t.resetTreeSignState();
    t.resetTreePermutationState();
    std::vector<int> currentPerm = t.getSignVector();
    std::cout << "Original shuffling is: " << std::endl;
    for(int a: currentPerm)
        std::cout << a << " ";
    std::cout << std::endl;
    std::cout << "Finished!" << std::endl;
}


void TestPermutationTree::testRandomSwapping(Eigen::MatrixXd& X, MultyRowArray &a, int n){
    PermutationTree t(a);
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

void TestPermutationTree::testRandomSignFlipping(Eigen::MatrixXd& X, MultyRowArray &a, int n){
    PermutationTree t(a);
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


//----------PUBLIC METHODS-----------------


TestPermutationTree::TestPermutationTree()
{
    //First matrix used for tests, no repetitions at all
    X1 = Eigen::MatrixXd(9, 2);

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
    //Here there are repetitions, specifically:
    //0 = 6
    //1 = 7
    //2 = 8
    X2 = Eigen::MatrixXd(9, 2);

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

    a1 = MultyRowArray(9,3);
    a1[0][0] = 1;
    a1[0][1] = 1;
    a1[0][2] = 1;
    a1[0][3] = 1;
    a1[0][4] = 1;
    a1[0][5] = 1;
    a1[0][6] = 1;
    a1[0][7] = 1;
    a1[0][8] = 1;

    a1[1][0] = -1;
    a1[1][1] = -1;
    a1[1][2] = -1;
    a1[1][3] = -2;
    a1[1][4] = -2;
    a1[1][5] = -2;
    a1[1][6] = -3;
    a1[1][7] = -3;
    a1[1][8] = -3;

    a2 = MultyRowArray(9,2);

    a2[0][0] = 1;
    a2[0][1] = 1;
    a2[0][2] = 1;
    a2[0][3] = 1;
    a2[0][4] = 1;
    a2[0][5] = 1;
    a2[0][6] = 1;
    a2[0][7] = 1;
    a2[0][8] = 1;
}

TestPermutationTree::~TestPermutationTree()
{

}

//-----------TEST CASES------------------

void TestPermutationTree::initTestCase(){

}

void TestPermutationTree::lAlgorithmtest1(){
    testLAlgorithmTree(X2, a1);
}

void TestPermutationTree::lAlgorithmtest2(){
    testLAlgorithmTree(X2, a2);
}

void TestPermutationTree::lAlgorithmtest3(){
    testLAlgorithmTree(X1, a1);
}

void TestPermutationTree::lAlgorithmtest4(){
    testLAlgorithmTree(X1, a2);
}

//For both EE and ISE assumptions, we use only multyRowArray1 since
//otherwise exhaustive approach won't end
void TestPermutationTree::allSignFlippingsAndPermutationsTest1(){
    testAllSignFlippingsAndPermutation(X1, a1);
}

void TestPermutationTree::allSignFlippingsAndPermutationsTest2(){
    testAllSignFlippingsAndPermutation(X2, a1);
}

void TestPermutationTree::allSignFlippingsTest1(){
    //We could also have used X2, doesn't really matter for sign flips
    testAllSignFlippingsTree(X1, a1);
}

void TestPermutationTree::allSignFlippingsTest2(){
    //We could also have used X2, doesn't really matter for sign flips
    testAllSignFlippingsTree(X1, a2);
}

void TestPermutationTree::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestPermutationTree)

#include "testpermutationtree.moc"
