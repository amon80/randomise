#include "treeblock.h"

TreeBlock::TreeBlock(int startBlockIndex, int endBlockIndex, int permutable)
    :startBlockIndex(startBlockIndex),
     endBlockIndex(endBlockIndex),
     permutable(permutable)
{

}

void TreeBlock::addSon(TreeBlock * son){
    sons.push_back(son);
}

int TreeBlock::getStartBlockIndex(){
    return startBlockIndex;
}

int TreeBlock::getEndBlockIndex(){
    return endBlockIndex;
}

void TreeBlock::addValue(float v){
    this->value = v;
}

