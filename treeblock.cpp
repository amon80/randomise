#include "treeblock.h"

TreeBlock::TreeBlock(std::vector<int>& indices, bool permutable)
    :indices(indices),
     permutable(permutable),
     threecolsarray(std::vector<std::vector<int>>(3))
{

}

TreeBlock::TreeBlock(bool permutable)
    :permutable(permutable),
    threecolsarray(std::vector<std::vector<int>>(3))
{

}


void TreeBlock::addSon(TreeBlock * son){
    sons.push_back(son);
}

void TreeBlock::setValue(int v){
    this->value = v;
}

int TreeBlock::getNumSons(){
    return sons.size();
}

int TreeBlock::getIndex(int i){
    return indices[i];
}

int TreeBlock::getIndicesSize(){
    return indices.size();
}

bool TreeBlock::isPermutable(){
    return permutable;
}

TreeBlock * TreeBlock::getSon(int i){
    return sons[i];
}

int TreeBlock::getValue(){
    return value;
}

// We're actually treating the three cols array
// as a three rows array
void TreeBlock::initializeThreeColsArray(){
    int numsons = sons.size();
    //first column is a sequence of integers that represente each of the branches.
    //It is inizialed to all -1 so that it can be filled later.
    threecolsarray[0] = std::vector<int>(numsons, -1);
    for(int i = 1; i < 3; i++){
        threecolsarray[i] = std::vector<int>(numsons);
    }
    //TODO: other stuff concerning third row basing on the state(permutable, nonpermutable)
    //of the block
}

//i: 0 <= i <= 2
std::vector<int>& TreeBlock::getArray(int i){
    return threecolsarray[i];
}

