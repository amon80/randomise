#include "statisticalmap4d.h"

StatisticalMap4D::StatisticalMap4D(int dim, int N)
    :dim(dim),
     N(N),
     voxels(std::vector<Eigen::VectorXd>(dim))
{
    for (int i = 0; i < dim; ++i)
        voxels[i] = Eigen::VectorXd::Zero(N);
}

StatisticalMap4D::StatisticalMap4D(int dimX, int dimY, int dimZ, int N)
    :dim(dimX*dimY*dimZ),
     N(N),
     voxels(std::vector<Eigen::VectorXd>(dim))
{
    for (int i = 0; i < dim; ++i)
        voxels[i] = Eigen::VectorXd(N);
}

Eigen::VectorXd& StatisticalMap4D::operator[](const std::size_t idx){
    return voxels[idx];
}

int StatisticalMap4D::getNumVoxels(){
    return dim;
}

int StatisticalMap4D::getNumMaps(){
    return N;
}
