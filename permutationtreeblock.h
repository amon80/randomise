#ifndef PERMUTATIONTREEBLOCK_H
#define PERMUTATIONTREEBLOCK_H

#include <vector>
#include "binarystring.h"
#include "threecolsarray.h"

class PermutationTreeBlock
{
public:
    //--------CONSTRUCTORS-----------
    PermutationTreeBlock(std::vector<int>& indices, bool permutable);
    PermutationTreeBlock(bool permutable);
    //--------MODIFIERS--------------
    void addSon(PermutationTreeBlock * son);
    void setValue(int value);
    //--------ACCESS METHODS---------
    int getIndex(int i);
    int getValue();
    int getNumSons();
    int getIndicesSize();
    bool isPermutable();
    PermutationTreeBlock * getSon(int i);
    //-------THREECOLS ARRAY METHODS----
    void initializeThreeColsArray();
    std::vector<int>& getArray(int i);
    //-------BINARY COUNTER METHODS-----
    void initializeBinaryCounter();
    BinaryString& getBinaryCounter();
private:
    std::vector<int> indices;
    bool permutable;
    std::vector<std::vector<int>> threecolsarray;
    int value;
    BinaryString counter;
    std::vector<PermutationTreeBlock*> sons;
};

#endif // PERMUTATIONTREEBLOCK_H
