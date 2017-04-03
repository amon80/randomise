#include "matrices.h"
#include "mymath.h"
#include <algorithm>
#include "Eigen/Core"
#include "Eigen/SVD"

Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm){
    int n = perm.size();
    Eigen::MatrixXd toReturn = Eigen::MatrixXd::Zero(n,n);
    for(int i = 0; i < n; i++){
        int rowIndex = myabs(perm[i]) - 1;
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

PartitioningResult partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd &C){
    //Partition the model
    PartitioningResult toReturn;
    Eigen::MatrixXd D = (M.transpose() * M).inverse();
    Eigen::MatrixXd Ctrasp = C.transpose();
    toReturn.X = M*D*C*((Ctrasp*D*C).inverse());

    int r = C.rows();
    int s = C.cols();
    if(r == s){
        toReturn.Z = Eigen::MatrixXd::Zero(M.rows(), 1);
    }
    else{
        //"Cu is a matrix whose columns span in the null space of C"
        Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
        Eigen::MatrixXd Cu = lu.kernel();
        Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse())*Ctrasp*D*Cu;
        toReturn.Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());
    }
    return toReturn;
}

