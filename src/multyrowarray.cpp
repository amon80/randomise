#include "multyrowarray.h"

MultyRowArray::MultyRowArray()
{

}

MultyRowArray::MultyRowArray(int nrows, int ncols)
    :array(std::vector<std::vector<int>>(ncols))
{
    for(int i = 0; i < ncols; i++){
        array[i] = std::vector<int>(nrows);
    }
    for(int i = 0; i < nrows; i++){
        array[ncols-1][i] = i+1;
    }

}

int MultyRowArray::size(){
    return array.size();
}

std::vector<int>& MultyRowArray::operator[](int index){
    return array[index];
}
