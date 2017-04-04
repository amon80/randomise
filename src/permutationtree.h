#ifndef PERMUTATIONTREE_H
#define PERMUTATIONTREE_H

#include <vector>
#include "Eigen/Dense"

class PermutationTreeBlock;

class PermutationTree
{
public:
    //----------CONSTRUCTOR------------
    PermutationTree(std::vector<std::vector<int>>& multyRowArray);
    //----------DESTRUCTOR-------------
    ~PermutationTree();
    //----------INITIALIZERS-----------
    void initializeThreeColsArray(PermutationTreeBlock *block = nullptr);
    void initializeBinaryCounters(PermutationTreeBlock *block = nullptr);
    int calculatePermutations(Eigen::MatrixXd& X, bool EE, bool ISE, PermutationTreeBlock * block = nullptr);
    //----------ACCESS METHODS---------
    //NOTE: getSignVector gets a permutation vector as well.
    std::vector<int> getPermutationVector(PermutationTreeBlock * block = nullptr);
    std::vector<int> getSignVector(PermutationTreeBlock * block = nullptr);
    std::vector<int> getMinimumSetOfVarianceGroups(PermutationTreeBlock * block = nullptr, int counter = 0);
    int getNumLeaves();
    //----------SEQUENTIAL SHUFFLINGS METHODS----
    //NOTE: this two function have sense only when listing all the possible
    //shufflings/sign flipping
    bool LAlgorithm(PermutationTreeBlock * block = nullptr, std::vector<PermutationTreeBlock*> * alreadyVisited = nullptr);
    bool signFlipping(PermutationTreeBlock * block = nullptr, std::vector<PermutationTreeBlock *> *alreadyVisited = nullptr);
    //NOTE: this method should be invoked once, at the beginning
    void reverseLAlgorithm(PermutationTreeBlock * block = nullptr);
    //----------RANDOM SHUFFLINGS METHODS--------
    void randomShuffle(PermutationTreeBlock * block = nullptr);
    void randomSignFlip(PermutationTreeBlock * block = nullptr);
    //----------RESET METHODS--------------------
    void resetTreePermutationState(PermutationTreeBlock * block = nullptr);
    void resetTreeSignState(PermutationTreeBlock * block = nullptr);
private:
    PermutationTreeBlock* root;
    int numleaves;
};

#endif // PERMUTATIONTREE_H
