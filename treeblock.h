#ifndef TREEBLOCK_H
#define TREEBLOCK_H

#include <vector>

class TreeBlock
{
public:
    TreeBlock(int startBlockIndex, int endBlockIndex, int permutable);
    void addSon(TreeBlock * son);
    int getStartBlockIndex();
    int getEndBlockIndex();
    void addValue(float v);
private:
    int startBlockIndex;
    int endBlockIndex;
    bool permutable;
    float value;
    std::vector<TreeBlock*> sons;
};

#endif // TREEBLOCK_H
