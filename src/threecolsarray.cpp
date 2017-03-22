#include "threecolsarray.h"
#include <algorithm>
#include <random>
#include <chrono>

//-------FRIEND FUNCTIONS--------

std::ostream& operator<<(std::ostream& os, const ThreeColsArray& obj){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < obj.nrows; j++)
            os << obj.array[i][j] << "\t";
        os << std::endl;
    }
    return os;
}

//----------METHODS---------------


ThreeColsArray::ThreeColsArray()
{

}

ThreeColsArray::ThreeColsArray(int nrows)
    :array(std::vector<std::vector<int>>(3)),
     nrows(nrows)
{
    for (int i = 0; i < 3; ++i)
        array[i] = std::vector<int>(nrows);
    //first col
    for(int i = 0; i < nrows; i++)
        array[0][i] = -1;
    //second and third col
    for(int i = 1; i < 3; i++)
        for(int j = 0; j < nrows; j++)
            array[i][j] = j;
}

bool ThreeColsArray::isLAlgorithmApplicable(){
    //L2

    int n = array[0].size() - 1;

    int jplus1 = n;
    int j = jplus1 -1;

    while(j >= 0){
        if(array[0][j] < array[0][jplus1])
            break;
         --j;
         --jplus1;
    }

    if(j == -1)
        return false;
    else
        return true;
}

void ThreeColsArray::swaprows(int index1, int index2){
    using std::swap;

    for(int i = 0; i < 3; i++)
        swap(array[i][index1], array[i][index2]);
}

void ThreeColsArray::randomSwapping(){
    //just before any swapping is performed third column is regenerated
    resetThirdColumn();

    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 g1 (seed);
    int n = array[0].size()-1;

    for (int i= n ; i > 0; --i) {
        std::uniform_int_distribution<int> d(0,i);
        int target = d(g1);
        if(i == target)
            continue;
        swaprows(i, target);
    }
}

void ThreeColsArray::lalgorithm1iteration(){
    //just before l algorithm application, third column is regenerated
    resetThirdColumn();

    //L2

    int n = array[0].size() - 1;

    int jplus1 = n;
    int j = jplus1 -1;

    while(j >= 0){
        if(array[0][j] < array[0][jplus1])
            break;
         --j;
         --jplus1;
    }

    //L3
    int l = n;
    while(l > j){
        if(array[0][j] < array[0][l]){
            swaprows(j, l);
            break;
        }
        --l;
    }

    //L4

    int k = jplus1;
    l = n;

    while(k < l){
        swaprows(l, k);
        k += 1;
        l -= 1;
    }
}

void ThreeColsArray::reset(){
    bool originalState = false;
    while(originalState){
        originalState = true;
        for(int i = 0; i < nrows; i++){
            int index = array[1][i];
            if(index == i)
                continue;
            swaprows(i, index);
        }
        for(int i = 0; i < nrows; i++){
            if(array[1][i] != i){
                originalState = false;
                break;
            }
        }
    }
    resetThirdColumn();
}

int& ThreeColsArray::operator()(int i, int j){
    return array[i][j];
}

int& ThreeColsArray::at(int i, int j){
    return array[i][j];
}

void ThreeColsArray::resetThirdColumn(){
    for(int i = 0; i < nrows; i++)
        array[2][i] = i;
}


