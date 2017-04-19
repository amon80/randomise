#ifndef MULTYROWARRAY_H
#define MULTYROWARRAY_H

#include <vector>

class MultyRowArray
{
public:
    MultyRowArray();
    MultyRowArray(int nrows, int ncols);
    std::vector<int>& operator[](int index);
    int size();
private:
    std::vector<std::vector<int>> array;
};

#endif // MULTYROWARRAY_H
