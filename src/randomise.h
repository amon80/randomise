#ifndef RANDOMISE_H
#define RANDOMISE_H

#include "statisticalmap3d.h"
#include "statisticalmap4d.h"
#include "Eigen\Dense"

struct RandomiseResult{
    StatisticalMap3D uncorrected;
    StatisticalMap3D corrected;
    StatisticalMap3D originalStatistic;
    std::vector<float> maxDistribution;
};

RandomiseResult randomise(StatisticalMap4D& Y, Eigen::MatrixXd& M, Eigen::MatrixXd &C, std::vector<std::vector<int>>& MultyRowArray, float (*pivotal)(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS), bool useTfce = true, bool EE = true, bool ISE = false, int J = 10000);

#endif // RANDOMISE_H
