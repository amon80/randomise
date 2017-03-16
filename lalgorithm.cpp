#include "lalgorithm.h"

void lalgorithm(std::vector<int>& list, std::ostream& stream){
    do{
        for(int a: list){
            stream << a;
        }
        stream << std::endl;
    }while(lalgorithm1iteration(list));
}

bool lalgorithm1iteration(std::vector<int>& list){
    //L2

    int jplus1 = list.size() - 1;
    int j = jplus1 -1;

    while(j >= 0){
        if(list[j] < list[jplus1])
            break;
         --j;
         --jplus1;
    }

    if(j == -1)
        return false;

    //L3

    int l = list.size() - 1;
    while(l > j){
        if(list[j] < list[l]){
            int tmp = list[l];
            list[l] = list[j];
            list[j] = tmp;
            break;
        }
        --l;
    }

    //L4

    int k = jplus1;
    l = list.size()-1;

    while(k < l){
        int tmp = list[l];
        list[l] = list[k];
        list[k] = tmp;

        k += 1;
    }
    return true;
}
