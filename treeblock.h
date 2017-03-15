#ifndef TREEBLOCK_H
#define TREEBLOCK_H

#include <vector>

class TreeBlock
{
public:
    TreeBlock(std::vector<int>& indices, bool permutable);
    TreeBlock(bool permutable);
    void addSon(TreeBlock * son);
    int getIndex(int i);
    void setValue(int value);
    int getNumSons();
    int getIndicesSize();
private:
    std::vector<int> indices;
    bool permutable;
    int value;
    std::vector<TreeBlock*> sons;
};

#endif // TREEBLOCK_H
