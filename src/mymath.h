#ifndef MYMATH_H
#define MYMATH_H

int fact(int n);
float elevate(float a, float b);
float multiply(float a, float b);
float add(float a, float b);
bool moreThan(float a, float b);
bool lessThan(float a, float b);

inline int myabs(int n){
    return n>=0 ? n : -n;
}

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif // MYMATH_H
