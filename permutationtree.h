#ifndef PERMUTATIONTREE_H
#define PERMUTATIONTREE_H

#include <vector>
#include <Eigen/Dense>

class PermutationTreeBlock;

class PermutationTree
{
public:
    //----------CONSTRUCTOR------------
    PermutationTree(std::vector<std::vector<int>>& multyRowArray);
    //----------INITIALIZERS-----------
    void initializeThreeColsArray(PermutationTreeBlock *block = nullptr);
    void initializeBinaryCounters(PermutationTreeBlock *block = nullptr);
    int calculatePermutations(Eigen::MatrixXd& X, bool EE, bool ISE, PermutationTreeBlock * block = nullptr);
    //----------ACCESS METHODS---------
    std::vector<int> getPermutationVector(PermutationTreeBlock * block = nullptr);
    std::vector<int> getSignVector(PermutationTreeBlock * block = nullptr);
    int getNumLeaves();
    //----------PERMUTATION METHODS----
    //Note: this two function have sense only when listing all the possible
    //shufflings/sign flipping
    bool LAlgorithm(PermutationTreeBlock * block = nullptr, std::vector<PermutationTreeBlock*> * alreadyVisited = nullptr);
    bool signFlipping(PermutationTreeBlock * block = nullptr, std::vector<PermutationTreeBlock *> *alreadyVisited = nullptr);
    void resetTreePermutationState(PermutationTreeBlock * block = nullptr);
    void resetTreeSignState(PermutationTreeBlock * block = nullptr);
private:
    PermutationTreeBlock* root;
    int numleaves;
};

#endif // PERMUTATIONTREE_H
