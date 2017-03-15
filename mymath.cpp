#include "mymath.h"

int fact(int n){
    int toReturn = 1;
    for(int i = 1; i<=n ; i++){
        toReturn *= i;
    }
    return toReturn;
}
