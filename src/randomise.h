#ifndef RANDOMISE_H
#define RANDOMISE_H

#include "statisticalmap3d.h"
#include "statisticalmap4d.h"
#include "Eigen/Dense"
#include "multyrowarray.h"

struct RandomiseResult{
    StatisticalMap3D uncorrected;
    StatisticalMap3D corrected;
    StatisticalMap3D originalStatistic;
    float criticalThreshold;
    int performedPermutations;
    std::vector<float> maxDistribution;
};

std::vector<RandomiseResult> randomise(StatisticalMap4D& Y, Eigen::MatrixXd& M, std::vector<Eigen::MatrixXd>& C, MultyRowArray &a, float (*pivotal)(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS), bool useTfce = true, float E = 0.5, float H = 2.0, float dh = 0.1, Connectivity3D * conn = nullptr, bool EE = true, bool ISE = false, int J = 10000, float alpha = 0.05);

#endif // RANDOMISE_H
