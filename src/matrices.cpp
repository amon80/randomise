#include "matrices.h"
#include "mymath.h"

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

//NOTE: maybe can be done better
void partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd& C, Eigen::MatrixXd& X, Eigen::MatrixXd& Z){
   Eigen::MatrixXd D = (M.transpose() * M).inverse();
   Eigen::MatrixXd Ctrasp = C.transpose();

   X = M*D*C*((Ctrasp*D*C).inverse());
   //Cu is a matrix whose columns span in the null space of C
   Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
   Eigen::MatrixXd Cu = lu.kernel();
   Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse());
   Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());
}
