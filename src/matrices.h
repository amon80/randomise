#ifndef MATRICES_H
#define MATRICES_H

#include "Eigen/Dense"
#include <vector>

struct PartitioningResult{
    Eigen::MatrixXd X;
    Eigen::MatrixXd Z;

    friend std::ostream & operator<<(std::ostream &os, const PartitioningResult& p);
};

//builds a shuffling matrix starting from a vector
Eigen::MatrixXd buildShufflingMatrix(std::vector<int>& perm);

//Function for PseudoInverse
Eigen::MatrixXd pseudoInverse(const Eigen::MatrixXd& a, double epsilon);

PartitioningResult partitionModel(Eigen::MatrixXd& X, Eigen::MatrixXd& c, Eigen::MatrixXd &W);

#endif // MATRICES_H
