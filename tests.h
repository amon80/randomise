#ifndef TESTS_H
#define TESTS_H

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

//Test #2: In particular: example #e from the paper is tried here
//Mixed experiment
void test2(Eigen::MatrixXd& X);

//Test #3: Same as test number 2, with simpler configuration
//Example #a -> Within block but not whole block
void test3(Eigen::MatrixXd& X);

//Test #4: Same as test number 3, with simpler configuration
//Example #b -> Whole block but not within block
void test4(Eigen::MatrixXd& X);

//Test #5: Same as test number 4, with simpler configuration
//Example #c -> Within block and whole block
void test5(Eigen::MatrixXd& X);

//Test #6: Same as test number 5, with simpler configuration
//Example #f -> unrestricted exchangeability
void test6(Eigen::MatrixXd& X);

void testBinaryStringsOperators();

void lalgorithmtest(ThreeColsArray& t);


#endif // TESTS_H
