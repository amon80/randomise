#include "mymath.h"
#include <cmath>

int fact(int n){
    int toReturn = 1;
    for(int i = 2; i<=n ; i++)
        toReturn *= i;
    return toReturn;
}

float elevate(float a, float b){
    return pow(a,b);
}

float multiply(float a, float b){
    return a*b;
}

float add(float a, float b) {
	return a+b;
}

bool moreThan(float a, float b){
    return a > b;
}

bool lessThan(float a, float b){
    return a < b;
}

