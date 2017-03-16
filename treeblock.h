#ifndef TREEBLOCK_H
#define TREEBLOCK_H

#include <vector>

class TreeBlock
{
public:
    //--------CONSTRUCTORS-----------
    TreeBlock(std::vector<int>& indices, bool permutable);
    TreeBlock(bool permutable);
    //--------MODIFIERS--------------
    void addSon(TreeBlock * son);
    void setValue(int value);
    //--------ACCESS METHODS---------
    int getIndex(int i);
    int getValue();
    int getNumSons();
    int getIndicesSize();
    bool isPermutable();
    TreeBlock * getSon(int i);
    //-------THREECOLS ARRAY METHODS----
    void initializeThreeColsArray();
    std::vector<int>& getArray(int i);
private:
    std::vector<int> indices;
    bool permutable;
    std::vector<std::vector<int>> threecolsarray;
    int value;

    std::vector<TreeBlock*> sons;
};

#endif // TREEBLOCK_H
