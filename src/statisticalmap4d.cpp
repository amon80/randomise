#include "statisticalmap4d.h"

StatisticalMap4D::StatisticalMap4D(int dim, int N)
    :dimX(-1),
     dimY(-1),
     dimZ(-1),
     dim(dim),
     N(N),
     voxels(std::vector<Eigen::VectorXd>(dim))
{
    for (int i = 0; i < dim; ++i)
        voxels[i] = Eigen::VectorXd::Zero(N);
}

StatisticalMap4D::StatisticalMap4D(int dimX, int dimY, int dimZ, int N)
    :dimX(dimX),
     dimY(dimY),
     dimZ(dimZ),
     dim(dimX*dimY*dimZ),
     N(N),
     voxels(std::vector<Eigen::VectorXd>(dim))
{
    for (int i = 0; i < dim; ++i)
        voxels[i] = Eigen::VectorXd(N);
}

Eigen::VectorXd& StatisticalMap4D::operator[](const std::size_t idx){
    return voxels[idx];
}

int StatisticalMap4D::getDimX(){
    return dimX;
}

int StatisticalMap4D::getDimY(){
    return dimY;
}

int StatisticalMap4D::getDimZ(){
    return dimZ;
}

int StatisticalMap4D::getNumVoxels(){
    return dim;
}

int StatisticalMap4D::getNumMaps(){
    return N;
}
