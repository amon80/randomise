#include "permutationtreeblock.h"
#include <utility>
#include <map>

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

void PermutationTreeBlock::permuteTreeUsingThreeColsArray(){
    int numsons = sons.size();
    //Copy the original order of the tree.
    std::vector<PermutationTreeBlock*> originalOrder(numsons);
    for(int i = 0; i < numsons; i++)
        originalOrder[i] = sons[i];
    //Now, let's build the new shuffling.
    for(int i = 0; i < numsons; i++){
        int index = threecolsarray(2,i);
        sons[i] = originalOrder[index];
    }
}


void PermutationTreeBlock::applyLAlgorithm(){
    threecolsarray.lalgorithm1iteration();
    permuteTreeUsingThreeColsArray();
}

void PermutationTreeBlock::randomSwapSons(){
    threecolsarray.randomSwapping();
    permuteTreeUsingThreeColsArray();
}

void PermutationTreeBlock::resetNodePermutationState(){
    int numsons = sons.size();
    //Copy the original order of the tree.
    std::vector<PermutationTreeBlock*> originalOrder(numsons);
    for(int i = 0; i < numsons; i++)
        originalOrder[i] = sons[i];
    //Now, let's restore the original shuffling.
    //NOTE: we can't use the same method as before, as here is REVERSE INDEXING
    for(int i = 0; i < numsons; i++){
        int index = threecolsarray(1,i);
        sons[index] = originalOrder[i];
    }
    threecolsarray.reset();
}

void PermutationTreeBlock::incrementCounter(){
    counter++;
}

void PermutationTreeBlock::resetCounter(){
    counter.reset();
}

void PermutationTreeBlock::setRandomCounter(){
    counter.generateRandomly();
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

bool PermutationTreeBlock::isLAlgorithmApplicable(){
    return permutable && threecolsarray.isLAlgorithmApplicable();
}

bool PermutationTreeBlock::isIncrementable(){
    return permutable && counter.isIncrementable();
}

PermutationTreeBlock * PermutationTreeBlock::getSon(int i){
    return sons[i];
}

int PermutationTreeBlock::getValue(){
    return value;
}

void PermutationTreeBlock::initializeThreeColsArray(){
    if(permutable)
        threecolsarray = ThreeColsArray(sons.size());
}

void PermutationTreeBlock::initializeBinaryCounter(){
    int numSons = sons.size();
    if(numSons == 0)
        counter = BinaryString();
    else
        counter = BinaryString(numSons);
}

BinaryString& PermutationTreeBlock::getBinaryCounter(){
    return counter;
}


ThreeColsArray& PermutationTreeBlock::getThreeColsArray(){
    return threecolsarray;
}

