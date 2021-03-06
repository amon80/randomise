#ifndef STATISTICALMAP4D_H
#define STATISTICALMAP4D_H

#include <vector>
#include "Eigen/Dense"

class StatisticalMap4D
{
public:
    //CONSTRUCTORS
    StatisticalMap4D();
    StatisticalMap4D(int dim, int N);
    StatisticalMap4D(int dimX, int dimY, int dimZ, int N);
    //MODIFIERS
    Eigen::VectorXd& operator[](const std::size_t idx);
    //ACCESS METHODS
    int getDimX();
    int getDimY();
    int getDimZ();
    int getNumVoxels();
    int getNumMaps();
private:
    //3d map dimensions
    int dimX;
    int dimY;
    int dimZ;
    //# of voxels
    int dim;
    //# of maps
    int N;
    std::vector<Eigen::VectorXd> voxels;
};

#endif // STATISTICALMAP4D_H
