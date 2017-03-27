#include "matrices.h"
#include "mymath.h"
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/SVD>

Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm){
    int n = perm.size();
    Eigen::MatrixXd toReturn = Eigen::MatrixXd::Zero(n,n);
    for(int i = 0; i < n; i++){
        int rowIndex = abs(perm[i]) - 1;
        if(perm[i] > 0)
            toReturn(i, rowIndex) = 1;
        else
            toReturn(i, rowIndex) = -1;
    }
    return toReturn;
}


Eigen::MatrixXd pseudoInverse(Eigen::MatrixXd& a, double epsilon)
{
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(a ,Eigen::ComputeThinU | Eigen::ComputeThinV);
    double tolerance = epsilon * std::max(a.cols(), a.rows()) *svd.singularValues().array().abs()(0);
    return svd.matrixV() *  (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0).matrix().asDiagonal() * svd.matrixU().adjoint();
}
