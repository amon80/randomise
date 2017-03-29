#include "mystat.h"
#include "mymath.h"
#include <cmath>


//usable only when s=rank(C)==1
float TStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    float FValue = FStatistic(phi, epsilon, M, C, s, VGS);
    float beta = phi(0);
    return sgn(beta)*sqrt(FValue);
}

float FStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    Eigen::MatrixXd Ctrasp = C.transpose();
    //M's rank is it's number of columns since the design matrix is full rank
    int r = M.cols();
    int rankM = r;
    int rankZ = r - s;
    int N = M.rows();
    Eigen::MatrixXd X = Eigen::MatrixXd::Zero(N, s);
    Eigen::VectorXd beta = Eigen::VectorXd::Zero(s);
    for(int i = 0; i < s; i++){
        for(int j = 0; j < N; j++){
            X(j,i) = M(j,i);
        }
    }
    for(int i = 0; i < s; i++)
        beta(i) = phi(i);
    Eigen::MatrixXd denominatorMatrix = (epsilon.transpose()*epsilon)/(N - rankM - rankZ);
    Eigen::MatrixXd numeratorMatrix = beta.transpose()*(X.transpose()*X)*beta;
    float denominator = denominatorMatrix(0,0);
    float numerator = numeratorMatrix(0,0);
    numerator /= s;
    if(denominator == 0)
        return 0;
    else
        return numerator/denominator;
}

float GStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd &C, int s, std::vector<int>& VGS){
    //TODO
    return 0;
}
