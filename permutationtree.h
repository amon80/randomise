#ifndef PERMUTATIONTREE_H
#define PERMUTATIONTREE_H

#include <vector>
#include <Eigen/Dense>

class PermutationTreeBlock;

class PermutationTree
{
public:
    PermutationTree(std::vector<std::vector<int>>& multyRowArray);
    void initializeThreeColsArray(PermutationTreeBlock *block = nullptr);
    void initializeBinaryCounters(PermutationTreeBlock *block = nullptr);
    int calculatePermutations(Eigen::MatrixXd& X, bool EE, bool ISE, PermutationTreeBlock * block = nullptr);
    //TODO: implement the following methods:
    //1) Given a tree, build a permutation matrix from it.
    //2) Given a tree, shuffle it so to obtain the next permutation matrix
    //3) The same two methods as above for the sign flipping matrix.
private:
    PermutationTreeBlock* root;
};

#endif // PERMUTATIONTREE_H
