#include "permutationtree.h"
#include "treeblock.h"

inline
int abs(int n){
    return n>=0 ? n : -n;
}

int findMax(std::vector<int>& v, int startIndex, int endIndex){
    int max = abs(v[startIndex]);
    for(int i = startIndex+1; i < endIndex; i++){
        int currentNumber = abs(v[i]);
        if(currentNumber > max)
            max = currentNumber;
    }
    return max;
}

int findStart(int numBlock, int startIndex, int endIndex, int currentRow, std::vector<std::vector<int>>& multyRowArray){
    for(int i = startIndex; i < endIndex; i++){
        if(abs(multyRowArray[currentRow][i]) == numBlock)
            return i;
    }
    return -1;
}

int findEnd(int numBlock, int startBlockIIndex, int endIndex, int currentRow, std::vector<std::vector<int>>& multyRowArray){
    if(endIndex - startBlockIIndex == 1)
        return endIndex;
    for(int i = startBlockIIndex; i < endIndex; i++){
        if(abs(multyRowArray[currentRow][i]) != numBlock)
            return i;
    }
    return multyRowArray[currentRow].size();
}

void buildTreeRecursively(TreeBlock * block, unsigned int currentRow, std::vector<std::vector<int>>& multyRowArray){
    if(currentRow == multyRowArray.size()-1){
        //base case
        int startIndex = block->getStartBlockIndex();
        int endIndex = block->getEndBlockIndex();
        for(int i = startIndex; i < endIndex; i++){
            //last row are actual observations, so indices don't make really sense
            TreeBlock * element = new TreeBlock(-1, -1, false);
            element->addValue(multyRowArray[currentRow][i]);
            block->addSon(element);
        }
        return;
    }
    int numSons = findMax(multyRowArray[currentRow], block->getStartBlockIndex(), block->getEndBlockIndex());
    //for(int i = 0; i < numSons; i++)
    //of course depends on how block are enumerated
    //here is assumed from 1 to numSons(included)
    for(int i = 1; i <= numSons; i++){
        int beginBlockI = findStart(i, block->getStartBlockIndex(), block->getEndBlockIndex(), currentRow, multyRowArray);
        int endBlockI = findEnd(i, beginBlockI, block->getEndBlockIndex(), currentRow,multyRowArray);
        bool permutable = false;
        if(multyRowArray[currentRow][beginBlockI] > 0)
            permutable = true;
        TreeBlock * sonI = new TreeBlock(beginBlockI, endBlockI, permutable);
        block->addSon(sonI);
        buildTreeRecursively(sonI, currentRow+1, multyRowArray);
    }
}

PermutationTree::PermutationTree(std::vector<std::vector<int>>& multyRowArray)
{
    bool permutable = false;
    if(multyRowArray[0][0] > 0)
        permutable = true;
    root = new TreeBlock(0, multyRowArray[0].size(), permutable);
    buildTreeRecursively(root, 1, multyRowArray);
}
