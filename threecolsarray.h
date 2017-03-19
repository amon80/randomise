#ifndef THREECOLSARRAY_H
#define THREECOLSARRAY_H

#include <vector>
#include <iostream>

class ThreeColsArray
{
public:
    ThreeColsArray();
    ThreeColsArray(int nrows);
    bool isLAlgorithmApplicable();
    void swaprows(int index1, int index2);
    void randomSwapping();
    void lalgorithm1iteration();
    void reset();
    int& operator()(int i, int j);
    void resetThirdColumn();
private:
    friend std::ostream& operator<<(std::ostream& os, const ThreeColsArray& obj);
    std::vector<std::vector<int>> array;
    int nrows;
};

#endif // THREECOLSARRAY_H
