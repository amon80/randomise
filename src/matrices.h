#ifndef MATRICES_H
#define MATRICES_H

#include <Eigen/Dense>
#include <vector>

//builds a shuffling matrix starting from a vector
Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm);

// Partion the design matrix M basing on the contrast C as indicated on the paper
//X contains the design for the regressors of interest and Z for nuisance variable
//Variables dimensionality:
//M is N x r
//C is r x s
//X is N x s
//Z is N x (r-s)
//with 1 <= s <=r
void partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd& C, Eigen::MatrixXd& X, Eigen::MatrixXd& Z);


#endif // MATRICES_H
