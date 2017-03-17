#include "permutationtreeblock.h"

PermutationTreeBlock::PermutationTreeBlock(std::vector<int>& indices, bool permutable)
    :indices(indices),
     permutable(permutable),
     threecolsarray(permutable ? std::vector<std::vector<int>>(3) : std::vector<std::vector<int>>(0))
{

}

PermutationTreeBlock::PermutationTreeBlock(bool permutable)
    :permutable(permutable),
    threecolsarray(permutable ? std::vector<std::vector<int>>(3) : std::vector<std::vector<int>>(0))
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
        //first column is a sequence of integers that represente each of the branches.
        //It is inizialed to all -1 so that it can be filled later.
        threecolsarray[0] = std::vector<int>(numsons, -1);
        for(int i = 1; i < 3; i++){
            threecolsarray[i] = std::vector<int>(numsons);
        }
        //second and third columns are rearrengements of indices
        //so their content at the beginning are just the indices in order
        //they have been filled separetly so code is clearer.
        int n = threecolsarray.size();
        for(int i = 1; i < n; i++){
            for(int j = 0; j < numsons; j++){
                 threecolsarray[i][j] = j;
            }
        }
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
std::vector<int>& PermutationTreeBlock::getArray(int i){
    return threecolsarray[i];
}

