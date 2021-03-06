#include "matrices.h"
#include "mymath.h"
#include <algorithm>
#include "Eigen/Core"
#include "Eigen/SVD"

std::ostream & operator<<(std::ostream &os, const PartitioningResult& p){
    os << "Matrix X:" << std::endl;
    os << p.X << std::endl;
    os << "Matrix Z:" << std::endl;
    os << p.Z << std::endl;
    return os;
}

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


Eigen::MatrixXd pseudoInverse(const Eigen::MatrixXd& a, double epsilon)
{
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(a ,Eigen::ComputeThinU | Eigen::ComputeThinV);
    double tolerance = epsilon * std::max(a.cols(), a.rows()) *svd.singularValues().array().abs()(0);
    return svd.matrixV() *  (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0).matrix().asDiagonal() * svd.matrixU().adjoint();
}

PartitioningResult partitionModel(Eigen::MatrixXd& X, Eigen::MatrixXd &c, Eigen::MatrixXd &W){
    //Partition the model

	double epsilon = std::numeric_limits<double>::epsilon();

    PartitioningResult toReturn;
    Eigen::MatrixXd Xtrasp = X.transpose();
	Eigen::MatrixXd Q = pseudoInverse((Xtrasp * X), epsilon);
	Eigen::MatrixXd Qw = pseudoInverse((Xtrasp * W * X), epsilon);
    Eigen::MatrixXd ctrasp = c.transpose();
	Eigen::MatrixXd F1 = pseudoInverse((ctrasp*Qw*c), epsilon);
    toReturn.X = X*Q*c*F1;

    int r = c.rows();
    int s = c.cols();
    if(r == s){
        toReturn.Z = Eigen::MatrixXd::Zero(X.rows(), 1);
    }
    else{
        //"c2 is a matrix whose COLUMNS span in the null space of C"
        Eigen::FullPivLU<Eigen::MatrixXd> lu(ctrasp);
        Eigen::MatrixXd c2 = lu.kernel();
        Eigen::MatrixXd Pc = c*F1*ctrasp*Q;
        Eigen::MatrixXd c3 = c2 - Pc*c2;
        Eigen::MatrixXd c3trasp = c3.transpose();
        Eigen::MatrixXd F3 = pseudoInverse((c3trasp*Q*c3), epsilon);
        toReturn.Z = X*Q*c3*F3;
    }
    return toReturn;
}

