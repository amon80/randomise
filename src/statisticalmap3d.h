#ifndef STATISTICALMAP3D_H
#define STATISTICALMAP3D_H

#include <iostream>

struct MinMaxStructure{
    float min;
    float max;
};

class StatisticalMap3D
{
public:
    //rule of five
    //constructors
    StatisticalMap3D();
    StatisticalMap3D(float * map, int dimX, int dimY, int dimZ);
    StatisticalMap3D(float * map, int dim);
    StatisticalMap3D(int dim);
    StatisticalMap3D(int dimX, int dimY, int dimZ);
    //destructor
    ~StatisticalMap3D();
    //copy semantics
    StatisticalMap3D(const StatisticalMap3D& rhs);
    StatisticalMap3D& operator=(const StatisticalMap3D& rhs);
    //move sematics
    StatisticalMap3D(StatisticalMap3D&& rhs);
    StatisticalMap3D& operator=(StatisticalMap3D&& rhs);
    //modifiers
    float& operator[](const std::size_t idx);
    StatisticalMap3D& operator/=(const float number);
    StatisticalMap3D& operator+=(StatisticalMap3D& rhs);
    void zeroMap(float(*confront)(const float));
    void flipMap();
    void applyOperation(float (* operation) (const float a, const float b), const float argument);
    float& operator()(const std::size_t idx, const std::size_t idy, const std::size_t idz);
    //access methods
    MinMaxStructure findMinMax();
    int size();
    int sizeX();
    int sizeY();
    int sizeZ();
private:
    friend std::ostream & operator<<(std::ostream &os, const StatisticalMap3D& p);
    friend void swap(StatisticalMap3D& first, StatisticalMap3D& second);
    friend std::istream& operator>>(std::istream &is, StatisticalMap3D& p);
    friend StatisticalMap3D operator+(StatisticalMap3D lhs, StatisticalMap3D& rhs);
    float * map;
    int dimX;
    int dimY;
    int dimZ;
    int dim;
};



#endif // STATISTICALMAP3D_H
