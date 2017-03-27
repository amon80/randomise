#include "mystat.h"

float FStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    Eigen::MatrixXd Ctrasp = C.transpose();
    //M's rank is it's number of columns
    int rankM = M.cols();
    int N = M.rows();
    Eigen::MatrixXd denominatorMatrix = (epsilon.transpose()*epsilon)/(N - rankM);
    Eigen::MatrixXd numeratorMatrix = phi.transpose()*C*(Ctrasp*((M.transpose()*M).inverse())*C)*Ctrasp*phi;
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
