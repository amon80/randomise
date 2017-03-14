#ifndef PERMUTATIONTREE_H
#define PERMUTATIONTREE_H

#include <vector>

class TreeBlock;

class PermutationTree
{
public:
    PermutationTree(std::vector<std::vector<int>>& multyRowArray);
private:
    TreeBlock* root;
};

#endif // PERMUTATIONTREE_H
