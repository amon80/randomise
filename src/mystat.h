#ifndef MYSTAT_H
#define MYSTAT_H

#include <Eigen/Dense>
#include <vector>

float TStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd& C, int s, std::vector<int>& VGS);
float FStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd &C, int s, std::vector<int>& VGS);
float GStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& M, Eigen::MatrixXd &C, int s, std::vector<int>& VGS);

#endif // MYSTAT_H
