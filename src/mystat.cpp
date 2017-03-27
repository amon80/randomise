#include "mystat.h"

float FStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    Eigen::MatrixXd Ctrasp = C.transpose();
    Eigen::FullPivLU<Eigen::MatrixXd> lu(M);
    int rankM = lu.rank();
    auto denominatorMatrix = (epsilon.transpose()*epsilon)/(M.rows() - rankM);
    auto numeratorMatrix = phi.transpose()*C*(Ctrasp*((M.transpose()*M).inverse())*C)*Ctrasp*phi;
    float denominator = denominatorMatrix(0,0);
    float numerator = numeratorMatrix(0,0);
    numerator /= s;
    return numerator/denominator;
}

float GStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd &C, int s, std::vector<int>& VGS){
    //TODO
    return 0;
}
