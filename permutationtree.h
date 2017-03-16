#ifndef PERMUTATIONTREE_H
#define PERMUTATIONTREE_H

#include <vector>
#include <Eigen/Dense>

class TreeBlock;

class PermutationTree
{
public:
    PermutationTree(std::vector<std::vector<int>>& multyRowArray);
    void initializeThreeColsArray(TreeBlock *block = nullptr);
    void initializeBinaryCounters(TreeBlock *block = nullptr);
    int calculatePermutations(Eigen::MatrixXd& X, bool EE, bool ISE, TreeBlock * block = nullptr);
private:
    TreeBlock* root;
};

#endif // PERMUTATIONTREE_H
