#include "treeblock.h"

TreeBlock::TreeBlock(std::vector<int>& indices, bool permutable)
    :indices(indices),
     permutable(permutable)
{

}

TreeBlock::TreeBlock(bool permutable)
    :permutable(permutable)
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
