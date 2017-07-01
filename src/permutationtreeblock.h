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
    //--------DESTRUCTOR-------------
    ~PermutationTreeBlock();
    //--------MODIFIERS--------------
    void addSon(PermutationTreeBlock * son);
    void setValue(int value);
    void applyLAlgorithm();
    void applyReverseLAlgorithm();
    void randomSwapSons();
    void resetNodePermutationState();
    void incrementCounter();
    void resetCounter();
    void setRandomCounter();
    //--------ACCESS METHODS---------
    int getIndex(int i);
    int getValue();
    int getNumSons();
    int getIndicesSize();
    bool isPermutable();
    bool isLeaf();
    bool isLAlgorithmApplicable();
    bool isReverseLAlgorithmApplicable();
    bool isIncrementable();
    PermutationTreeBlock * getSon(int i);
    //-------THREECOLS ARRAY METHODS----
    void initializeThreeColsArray();
    ThreeColsArray& getThreeColsArray();
    //-------BINARY COUNTER METHODS-----
    void initializeBinaryCounter();
    BinaryString& getBinaryCounter();
private:
    void permuteTreeUsingThreeColsArray();
    std::vector<int> indices;
    bool permutable;
    ThreeColsArray threecolsarray;
    int value;
    BinaryString counter;
    std::vector<PermutationTreeBlock*> sons;
};

#endif // PERMUTATIONTREEBLOCK_H
