#ifndef MATRICES_H
#define MATRICES_H

#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/SVD>
#include <vector>
#include <utility>

//builds a shuffling matrix starting from a vector
Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm);

template<typename _Matrix_Type_>
_Matrix_Type_ pseudoInverse(const _Matrix_Type_ &a, double epsilon = std::numeric_limits<double>::epsilon());

#endif // MATRICES_H
