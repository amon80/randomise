#include "statisticalmap3d.h"

// ---------- FRIEND METHODS ---------------
std::ostream & operator<<(std::ostream &os, const StatisticalMap3D& p){
    os << p.dim << "\n";
    os << p.dimX << "\n";
    os << p.dimY << "\n";
    os << p.dimZ << "\n";
    for (int i = 0; i < p.dim; ++i) {
        os << p.map[i];
        if (i != p.dim - 1)
            os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream &is, StatisticalMap3D& p){
    int i = 0;
    is >> p.dim;
    is >> p.dimX;
    is >> p.dimY;
    is >> p.dimZ;
    float value;
    if(p.map == nullptr)
        p.map = new float[p.dim];
    while(is >> value){
        p.map[i++] = value;
    }
    return is;
}


void swap(StatisticalMap3D& first, StatisticalMap3D& second){
    using std::swap;

    swap(first.dim, second.dim);
    swap(first.dimX, second.dimX);
    swap(first.dimY, second.dimY);
    swap(first.dimZ, second.dimZ);
    swap(first.map, second.map);

}

StatisticalMap3D operator+(StatisticalMap3D lhs, StatisticalMap3D& rhs){
    lhs += rhs;
    return lhs;
}

//-------------- CONSTRUCTORS ------------------
StatisticalMap3D::StatisticalMap3D()
    :map(nullptr),
     dimX(0),
     dimY(0),
     dimZ(0),
     dim(0)
{

}

StatisticalMap3D::StatisticalMap3D(int dim)
    :map(new float[dim]),
     dimX(-1),
     dimY(-1),
     dimZ(-1),
     dim(dim)

{
    for (int i = 0; i < dim; ++i) {
        this->map[i] = 0;
    }
}

StatisticalMap3D::StatisticalMap3D(int dimX, int dimY, int dimZ)
    :map(new float[dimX*dimY*dimZ]),
     dimX(dimX),
     dimY(dimY),
     dimZ(dimZ),
     dim(dimX*dimY*dimZ)
{
    for (int i = 0; i < dim; ++i) {
        this->map[i] = 0;
    }
}

StatisticalMap3D::StatisticalMap3D(float* map, int dimX, int dimY, int dimZ)
    :map(new float[dimX*dimY*dimZ]),
     dimX(dimX),
     dimY(dimY),
     dimZ(dimZ),
     dim(dimX*dimY*dimZ)
{
    for (int i = 0; i < dim; ++i) {
        this->map[i] = map[i];
    }
}

StatisticalMap3D::StatisticalMap3D(float * map, int dim)
    :map(new float[dim]),
     dimX(-1),
     dimY(-1),
     dimZ(-1),
     dim(dim)
{
    for (int i = 0; i < dim; ++i) {
        this->map[i] = map[i];
    }
}

//--------- DESTRUCTOR ----------------
StatisticalMap3D::~StatisticalMap3D(){
    delete [] map;
}


//--------- COPY SEMANTICS --------------
StatisticalMap3D::StatisticalMap3D(const StatisticalMap3D& rhs)
    :map(new float[rhs.dim]),
     dimX(rhs.dimX),
     dimY(rhs.dimY),
     dimZ(rhs.dimZ),
     dim(rhs.dim)
{
    for (int i = 0; i < dim; ++i) {
        this->map[i] = rhs.map[i];
    }
}

StatisticalMap3D& StatisticalMap3D::operator=(const StatisticalMap3D& rhs){
    StatisticalMap3D tmp(rhs);
    swap(*this, tmp);
    return *this;
}


//----------- MOVE SEMANTICS ------------
StatisticalMap3D::StatisticalMap3D(StatisticalMap3D&& rhs)
    : StatisticalMap3D()
{
    swap(*this, rhs);
}

StatisticalMap3D& StatisticalMap3D::operator=(StatisticalMap3D&& rhs){
    swap(*this, rhs);
    return *this;
}

//---------- MODIFIERS -----------------

float& StatisticalMap3D::operator[](const std::size_t idx){
    return map[idx];
}

StatisticalMap3D& StatisticalMap3D::operator/=(const float number){
    for (int i = 0; i < dim; ++i) {
        this->map[i] /= number;
    }
    return *this; // return the result by reference
}

StatisticalMap3D& StatisticalMap3D::operator+=(StatisticalMap3D& rhs){
    for (int i = 0; i < dim; ++i) {
        map[i] += rhs.map[i];
    }
    return *this;
}

void StatisticalMap3D::flipMap(){
    for (int i = 0; i < dim; ++i)
        if(map[i] != 0)
            map[i] = -map[i];
}

void StatisticalMap3D::applyOperation(float (* operation) (const float a, const float b), const float argument){
    for (int i = 0; i < dim; ++i)
        map[i] = operation(map[i], argument);
}

float& StatisticalMap3D::operator()(const std::size_t idx, const std::size_t idy, const std::size_t idz){
    return map[idz*dimX*dimY + idy*dimY + idx];
}

MinMaxStructure StatisticalMap3D::findMinMax(){
    MinMaxStructure toReturn;
    toReturn.min = map[0];
    toReturn.max = map[0];

    for (int i = 1; i < dim; ++i){
       if(toReturn.min > map[i])
           toReturn.min = map[i];
       if(toReturn.max < map[i])
           toReturn.max = map[i];
    }

    return toReturn;
}

//------------- ACCESS METHODS ----------------

int StatisticalMap3D::size(){
    return dim;
}

int StatisticalMap3D::sizeX(){
    return dimX;
}
int StatisticalMap3D::sizeY(){
    return dimY;
}
int StatisticalMap3D::sizeZ(){
    return dimZ;
}
