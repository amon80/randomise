#ifndef MYMATH_H
#define MYMATH_H

int fact(int n);
inline int abs(int n){
    return n>=0 ? n : -n;
}

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


#endif // MYMATH_H
