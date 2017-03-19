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

//rowToUse can be 1 -> reset or 2 -> next permutation
void PermutationTreeBlock::permuteTreeUsingThreeColsArray(int rowToUse){
    int numsons = sons.size();
    std::map<int, int> swappings;
    for(int i = 0; i < numsons; i++){
        int index = threecolsarray(rowToUse,i);
        if(index == i)
            continue;
        //BUG! Elements gets swapped twice (third row) <- Seems to be corrected by using a swappings map
        if(!swappings.count(index)){
            swappings[i] = index;
            swapSons(i, index);
        }
        else{
            if(swappings[index] != i)
                swapSons(i, index);
        }
    }
}

void PermutationTreeBlock::applyLAlgorithm(){
    threecolsarray.lalgorithm1iteration();
    //The third column is the one that effectively permutes branches
    permuteTreeUsingThreeColsArray(2);
}

void PermutationTreeBlock::randomSwapSons(){
    threecolsarray.randomSwapping();
    permuteTreeUsingThreeColsArray(2);
}


void PermutationTreeBlock::swapSons(int index1, int index2){
    using std::swap;

    swap(sons[index1], sons[index2]);
}

void PermutationTreeBlock::resetNodePermutationState(){
    permuteTreeUsingThreeColsArray(1);
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

