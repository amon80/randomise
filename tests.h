#ifndef TESTS_H
#define TESTS_H

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

void testLAlgorithmTree(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray);
void testBinaryCounterTree(Eigen::MatrixXd& X, std::vector<std::vector<int>>& multyRowArray);

void testBinaryStringsOperators(int n);

void lalgorithmtest(ThreeColsArray& t);

void randomSwappingTest(ThreeColsArray& t, int num_iteration);


#endif // TESTS_H
