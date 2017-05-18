#include "mystat.h"
#include "mymath.h"
#include "matrices.h"
#include <cmath>
#include <algorithm>


//usable only when s=rank(C)==1
float TStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& partitionedM, Eigen::MatrixXd& unpartitionedM, Eigen::MatrixXd& Pj, Eigen::MatrixXd& R, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    float FValue = FStatistic(phi, epsilon, partitionedM, unpartitionedM, Pj, R, C, s, VGS);
    float beta = phi(0);
    return sgn(beta)*sqrt(FValue);
}

float FStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& partitionedM, Eigen::MatrixXd& unpartitionedM, Eigen::MatrixXd& Pj, Eigen::MatrixXd& R, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    int r = partitionedM.cols();
    int rankZ = r - s;
    int N = partitionedM.rows();
    //Getting X and beta
    Eigen::MatrixXd X = Eigen::MatrixXd::Zero(N, s);
    Eigen::VectorXd beta = Eigen::VectorXd::Zero(s);
    for(int i = 0; i < s; i++){
        for(int j = 0; j < N; j++){
            X(j,i) = partitionedM(j,i);
        }
    }
    for(int i = 0; i < s; i++)
        beta(i) = phi(i);
    int rankX = X.cols();
    Eigen::MatrixXd denominatorMatrix = (epsilon.transpose()*epsilon)/(N - rankX - rankZ);
    Eigen::MatrixXd numeratorMatrix = beta.transpose()*(X.transpose()*X)*beta;
    float denominator = denominatorMatrix(0,0);
    float numerator = numeratorMatrix(0,0);
    numerator /= s;
    if(denominator == 0)
        return 0;
    else
        return numerator/denominator;
}

//W is different for each voxel since the error is computed as epsilon = RY = (I - MM^+)Y
Eigen::MatrixXd computeW(Eigen::MatrixXd& R, Eigen::VectorXd& epsilon, std::vector<int>& VGS){
    int N = VGS.size();
    //Initializing as identity matrix
    Eigen::MatrixXd toReturn = Eigen::MatrixXd::Identity(N, N);

    //Filling the diagonal
    for(int i = 0; i < N; i++){
        float sum = 0;
        Eigen::VectorXd epsilonGroup = Eigen::VectorXd::Zero(N);
        for(int j = 0; j < N; j++){
            if(VGS[j] == VGS[i]){
                sum += R(j,j);
                epsilonGroup(j) = epsilon(j);
            }
        }
        toReturn(i,i) = sum / (epsilonGroup.dot(epsilonGroup));
    }
    return toReturn;
}

float computeLambda(int s, Eigen::MatrixXd& R, Eigen::MatrixXd& W, std::vector<int>& VGS){
    float term1 = 1;
    float term2 = 0;
    float term3 = 0;

    int N = VGS.size();

    //Computing term2
    float sFloat = (float) s;
    term2 = 2*((sFloat-1)/sFloat*(s+2));

    if(term2 == 0)
        return 1;

    //Computing term3
    int ngroups = (*std::max_element(VGS.begin(), VGS.end()));
    for(int i = 1; i <= ngroups; i++){
        float term30 = 0;
        for(int j = 0; j < N; j++){
            if(VGS[j] == i){
                term30 += R(j,j);
            }
        }
        float term31 = 1/term30;
        float term40 = 0;
        for(int j = 0; j < N; j++){
            if(VGS[j] == i){
                term40 += W(j,j);
            }
        }
        term40 /= W.trace();
        float term41 = 1 - term40;
        term3 += term31*term41;
    }

    return term1 + term2*term3;
}

float GStatistic(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& partitionedM, Eigen::MatrixXd& unpartitionedM, Eigen::MatrixXd& Pj, Eigen::MatrixXd& R, Eigen::MatrixXd& C, int s, std::vector<int>& VGS){
    int N = partitionedM.rows();

    //Getting X and beta
    Eigen::MatrixXd X = Eigen::MatrixXd::Zero(N, s);
    Eigen::VectorXd beta = Eigen::VectorXd::Zero(s);
    for(int i = 0; i < s; i++){
        for(int j = 0; j < N; j++){
            X(j,i) = partitionedM(j,i);
        }
    }
    for(int i = 0; i < s; i++)
        beta(i) = phi(i);

    Eigen::MatrixXd W = computeW(R, epsilon, VGS);
    float lambda = computeLambda(s, R, W, VGS);

    PartitioningResult p = partitionModel(unpartitionedM, C, W);
    Eigen::MatrixXd Xw = p.X;
    Eigen::MatrixXd Xwj = Pj*Xw;

    Eigen::MatrixXd numeratorMatrix = beta.transpose()*(Xwj.transpose()*X)*beta;
    float denominator = lambda*s;
    float numerator = numeratorMatrix(0,0);
    if(denominator == 0)
        return 0;
    else
        return numerator/denominator;
    return 0;
}

