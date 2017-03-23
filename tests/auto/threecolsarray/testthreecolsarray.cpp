#include <QtTest>
#include "threecolsarray.h"
#include "mymath.h"
#include <chrono>
#include <random>

class TestThreeColsArray : public QObject
{
    Q_OBJECT

public:
    TestThreeColsArray();
    ~TestThreeColsArray();

private:
    ThreeColsArray t1;
    ThreeColsArray t2;
    ThreeColsArray t3;
    int numIteration;
    void testLAlgorithm(ThreeColsArray& t);
    void testRandomShuffling(ThreeColsArray& t, int numIteration);
    void checkInitializationAndReset(ThreeColsArray& t);
private slots:
    void initTestCase();
    void lalgorithmtest1();
    void lalgorithmtest2();
    void lalgorithmtest3();
    void randomSwappingTest1();
    void randomSwappingTest2();
    void randomSwappingTest3();
    void cleanUpTestCase();
};


//--------PRIVATE METHODS---------------

void TestThreeColsArray::checkInitializationAndReset(ThreeColsArray &t){
    int nrows = t.getNumRows();

    for(int i = 0; i < nrows; i++){
        QCOMPARE(t(1,i), i);
        QCOMPARE(t(2,i), i);
    }
}

void TestThreeColsArray::testRandomShuffling(ThreeColsArray &t, int num_iteration){
    std::cout << "Iteration 0 - array status:" << std::endl;
    std::cout << t << std::endl;
    for(int i = 1; i <= num_iteration; i++){
        t.randomSwapping();
        std::cout << "Iteration " << i << " - array status:" << std::endl;
        std::cout << t << std::endl;
    }
    std::cout << "Finished permutations, trying reset" << std::endl;
    t.reset();
    checkInitializationAndReset(t);
    std::cout << t << std::endl;
}

void TestThreeColsArray::testLAlgorithm(ThreeColsArray& t){
    int iteration_number = 0;
    //Calculating number of iteration of L algorithm
    int nrows = t.getNumRows();
    int max = t(0,0);
    for(int i = 1; i < nrows; i++){
        if(max < t(0,i))
            max = t(0,i);
    }

    int expected_iterations = fact(nrows);
    if(max < nrows-1){
        for(int i = 0; i <= max; i++){
            int timesThatIrepeates = 0;
            for(int j = 0; j < nrows; j++){
                if(t(0,j) == i)
                    timesThatIrepeates++;
            }
            expected_iterations /= fact(timesThatIrepeates);
        }
    }

    while(true){
        if(t.isReverseLAlgorithmApplicable())
            t.reverselalgorithm1iteration();
        else
            break;
    }

    //Executing L algorithm.
    while(true){
        std::cout << "Iteration " << iteration_number++ << " - array status:" << std::endl;
        std::cout << t << std::endl;
        if(t.isLAlgorithmApplicable())
            t.lalgorithm1iteration();
        else
            break;
    }

    //Comparing the number of iterations performed
    QCOMPARE(iteration_number, expected_iterations);
    std::cout << "Finished permutations, trying reset" << std::endl;

    //Testing reset
    t.reset();
    checkInitializationAndReset(t);
    std::cout << t << std::endl;
}

//-----------PUBLIC METHODS-------------

//------CONSTRUCTOR AND DESTRUCTOR------

TestThreeColsArray::TestThreeColsArray()
{
    t1 = ThreeColsArray(6);
    t2 = ThreeColsArray(6);
    t3 = ThreeColsArray(6);

    //first three cols array has no repeated elements
    for(int i = 0; i < 6; i++){
        t1(0, i) = i;
    }

    //second three cols array has one or more repeated elements
    t2(0, 0) = 0;
    t2(0, 1) = 0;
    t2(0, 2) = 1;
    t2(0, 3) = 2;
    t2(0, 4) = 2;
    t2(0, 5) = 3;

    //third three cols array has one or more repeated elements, and at the
    //beginning its not in order

    t3(0, 0) = 0;
    t3(0, 1) = 1;
    t3(0, 2) = 0;
    t3(0, 3) = 2;
    t3(0, 4) = 2;
    t3(0, 5) = 0;


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g1 (seed);

    std::uniform_int_distribution<int> d(1,100);
    numIteration = d(g1);

}

TestThreeColsArray::~TestThreeColsArray()
{

}

//--------------TEST CASES--------------

void TestThreeColsArray::initTestCase(){
    checkInitializationAndReset(t1);
    checkInitializationAndReset(t2);
    checkInitializationAndReset(t3);
}

void TestThreeColsArray::lalgorithmtest1(){
    testLAlgorithm(t1);
}

void TestThreeColsArray::lalgorithmtest2(){
    testLAlgorithm(t2);
}

void TestThreeColsArray::lalgorithmtest3(){
    testLAlgorithm(t3);
}

void TestThreeColsArray::randomSwappingTest1(){
   testRandomShuffling(t1, numIteration);
}

void TestThreeColsArray::randomSwappingTest2(){
   testRandomShuffling(t2, numIteration);
}

void TestThreeColsArray::randomSwappingTest3(){
   testRandomShuffling(t3, numIteration);
}

void TestThreeColsArray::cleanUpTestCase(){

}

QTEST_APPLESS_MAIN(TestThreeColsArray)

#include "testthreecolsarray.moc"
