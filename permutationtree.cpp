#include "permutationtree.h"
#include "treeblock.h"

inline
int abs(int n){
    return n>=0 ? n : -n;
}

int findMax(std::vector<int>& v, TreeBlock * block){
    int n = block->getIndicesSize();
    int max = abs(v[block->getIndex(0)]);
    for(int i = 1; i < n; i++){
        int currentNumber = abs(v[block->getIndex(i)]);
        if(currentNumber > max)
            max = currentNumber;
    }
    return max;
}

std::vector<int> findIndices(std::vector<int>& row, int block_number, TreeBlock * block){
    std::vector<int> indices;
    int n = block->getIndicesSize();
    for(int i = 0; i < n; i++){
        if(abs(row[block->getIndex(i)]) == block_number)
            indices.push_back(block->getIndex(i));
    }
    return indices;
}

void buildTreeRecursively(TreeBlock * block, unsigned int currentRow, std::vector<std::vector<int>>& multyRowArray){
    //base case
    if(currentRow == multyRowArray.size()-1){
        int n = block->getIndicesSize();
        for(int i = 0; i < n; i++){
            //last row are actual observations, so indices don't make really sense
            TreeBlock * element = new TreeBlock(false);
            element->setValue(multyRowArray[currentRow][block->getIndex(i)]);
            block->addSon(element);
        }
        return;
    }
    //recursion
    int numSons = findMax(multyRowArray[currentRow], block);
    //for(int i = 0; i < numSons; i++)
    //of course depends on how block are enumerated
    //here is assumed from 1 to numSons(included)
    for(int i = 1; i <= numSons; i++){
        std::vector<int> indices = findIndices(multyRowArray[currentRow], i, block);
        bool permutable = false;
        if(multyRowArray[currentRow][indices[0]] > 0)
            permutable = true;
        TreeBlock * sonI = new TreeBlock(indices, permutable);
        block->addSon(sonI);
        buildTreeRecursively(sonI, currentRow+1, multyRowArray);
    }
}

PermutationTree::PermutationTree(std::vector<std::vector<int>>& multyRowArray)
{
    bool permutable = false;
    if(multyRowArray[0][0] > 0)
        permutable = true;
    int n = multyRowArray[0].size();
    std::vector<int> indices(n);
    for(int i = 0; i < n; i++){
        indices[i] = i;
    }
    root = new TreeBlock(indices, permutable);
    buildTreeRecursively(root, 1, multyRowArray);
}
