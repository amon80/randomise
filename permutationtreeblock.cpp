#include "permutationtreeblock.h"

PermutationTreeBlock::PermutationTreeBlock(std::vector<int>& indices, bool permutable)
    :indices(indices),
     permutable(permutable)
{

}

PermutationTreeBlock::PermutationTreeBlock(bool permutable)
    :permutable(permutable)
{

}

void PermutationTreeBlock::addSon(PermutationTreeBlock * son){
    sons.push_back(son);
}

void PermutationTreeBlock::setValue(int v){
    this->value = v;
}

int PermutationTreeBlock::getNumSons(){
    return sons.size();
}

int PermutationTreeBlock::getIndex(int i){
    return indices[i];
}

int PermutationTreeBlock::getIndicesSize(){
    return indices.size();
}

bool PermutationTreeBlock::isPermutable(){
    return permutable;
}

PermutationTreeBlock * PermutationTreeBlock::getSon(int i){
    return sons[i];
}

int PermutationTreeBlock::getValue(){
    return value;
}

// We're actually treating the three cols array
// as a three rows array
void PermutationTreeBlock::initializeThreeColsArray(){
    if(permutable){
        int numsons = sons.size();
        threecolsarray = ThreeColsArray(numsons);
    }
}

void PermutationTreeBlock::initializeBinaryCounter(){
    if(permutable){
        int numSons = sons.size();
        counter = BinaryString(numSons);
    }
}

BinaryString& PermutationTreeBlock::getBinaryCounter(){
    return counter;
}


//i: 0 <= i <= 2
//getArray can be called succesfully only if block is permutable
ThreeColsArray& PermutationTreeBlock::getThreeColsArray(){
    return threecolsarray;
}

