#ifndef TESTS_H
#define TESTS_H

//test #1: Testing the functions that computes the number of permutations
//With exchangeability blocks
void test1(int argc, char *argv[]);

//-----------------TESTS FOR MULTY LEVEL PERMUTATION-------------------

//Test #2: In particular: example #f from the paper is tried here
//Mixed experiment
void test2(int argc, char *argv[]);

//Test #3: Same as test number 2, with simpler configuration
//Example #a -> Within block but not whole block
void test3(int argc, char *argv[]);

//Test #4: Same as test number 3, with simpler configuration
//Example #b -> Whole block but not within block
void test4(int argc, char *argv[]);

//Test #5: Same as test number 4, with simpler configuration
//Example #c -> Within block and whole block
void test5(int argc, char *argv[]);

//Test #6: Same as test number 5, with simpler configuration
//Example #f -> unrestricted exchangeability
void test6(int argc, char *argv[]);

#endif // TESTS_H
