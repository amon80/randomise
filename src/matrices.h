#ifndef MATRICES_H
#define MATRICES_H

#include <Eigen/Dense>
#include <vector>

//builds a shuffling matrix starting from a vector
Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm);

//Function for PseudoInverse
//NOTE: doesn't work
Eigen::MatrixXd pseudoInverse(Eigen::MatrixXd& a, double epsilon);

#endif // MATRICES_H
