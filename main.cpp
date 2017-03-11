#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>

// Partion the design matrix M basing on the contrast C as indicated on the paper
//X contains the design for the regressors of interest and Z for nuisance variable
//Variables dimensionality:
//M is N x r
//C is r x s
//X is N x s
//Z is N x (r-s)
//with 1 <= s <=r

void partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd& C, Eigen::MatrixXd& X, Eigen::MatrixXd& Z){
   Eigen::MatrixXd D = (M.transpose() * M).inverse();
   Eigen::MatrixXd Ctrasp = C.transpose();

   X = M*D*C*((Ctrasp*D*C).inverse());
   Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
   Eigen::MatrixXd Cu = lu.kernel();
   Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse());
   Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());
}

//block are enumerated from 1 to nblock
int calculateMaxShufflings(Eigen::MatrixXd& X, Eigen::VectorXd& b, bool PB, bool EE, bool ISE){
    if(!PB){//within-block exchangeability
        int numblocks = findMax(b);
        for (int i = 0; i < numblocks; ++i) {

        }
    }else{//whole-block exchangeability

    }
    return 0;
}

int main(int argc, char *argv[])
{
    Eigen::MatrixXd m(4,2);
    m(0, 0) = 0;
    m(1, 0) = 0;
    m(2, 0) = 0;
    m(3, 0) = 1;

    m(0, 1) = 0;
    m(1, 1) = 0;
    m(2, 1) = 1;
    m(3, 1) = 0;
    std::cout << "Matrix m:" << std::endl;
    std::cout << m << std::endl;
    Eigen::MatrixXd mtrasp = m.transpose();
    Eigen::FullPivLU<Eigen::MatrixXd> lu(mtrasp);
    Eigen::MatrixXd A_null_space = lu.kernel();
    std::cout << "Matrix m null space:" << std::endl;
    std::cout << A_null_space << std::endl;
  return 0;
}
