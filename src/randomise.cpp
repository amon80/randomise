#include "randomise.h"
#include "permutationtree.h"
#include "matrices.h"
#include <random>
#include <limits>
#include <algorithm>
#include <vector>
#include <omp.h>

std::vector<RandomiseResult> randomise(StatisticalMap4D& Y, Eigen::MatrixXd& M, std::vector<Eigen::MatrixXd> &C, std::vector<std::vector<int>>& MultyRowArray, float (*pivotal)(Eigen::VectorXd &, Eigen::VectorXd &, Eigen::MatrixXd &, Eigen::MatrixXd &, int, std::vector<int> &), bool useTfce, bool EE, bool ISE, int J){
    //Storing number of observations for convinieance
    int N = Y.getNumMaps();

    //Initializing the vector of results
    std::vector<RandomiseResult> toReturn(C.size());

    int index = 0;
    for(Eigen::MatrixXd c: C){
        //NOTE: This has to be done here
        //since the partitioning changes with each
        //contrast.
        //Building the permutation tree
        PermutationTree t(MultyRowArray);
        t.initializeBinaryCounters();
        t.initializeThreeColsArray();

        //Partitioning the model and computing the rank of the contrast
        PartitioningResult partitioning = partitionModel(M, c);
        Eigen::MatrixXd X = partitioning.X;
        Eigen::MatrixXd Z = partitioning.Z;
        int s = c.cols();
        int r = c.rows();

        //"For semplicity, replace M"
        if(r != s){
            Eigen::MatrixXd tmp(X.rows(), X.cols()+Z.cols());
            tmp << X, Z;
            M = tmp;
        }
        else{
            M = X;
        }

        //Storing the identity matrix for convenience
        Eigen::MatrixXd I = Eigen::MatrixXd::Identity(N, N);

        //Computing the # number of permutations
        int Jmax = t.calculatePermutations(X, EE, ISE);

        //Computing the minimum set of VGS
        std::vector<int> VGS = t.getMinimumSetOfVarianceGroups();

        //NOTE: if J >= Jmax then we're going exhaustively
        bool exhaustively = false;
        int actualPermutationSize = 0;
        if(J >= Jmax){
            exhaustively = true;
            actualPermutationSize = Jmax;
            t.reverseLAlgorithm();
        }else{
            actualPermutationSize = J;
        }


        //Let's risolve the original model.
        //First, we get the informations that we need from the 4D map
        int numVoxels = Y.getNumVoxels();
        int dimX = Y.getDimX();
        int dimY = Y.getDimY();
        int dimZ = Y.getDimZ();

        //Then, we inizialize counters for uncorrected and corrected pvalues
        toReturn[index].corrected = StatisticalMap3D(dimX, dimY, dimZ);
        toReturn[index].uncorrected = StatisticalMap3D(dimX, dimY, dimZ);

        //Also, we inizialize a 3dmap to store the statistic on the
        //original permutation
        toReturn[index].originalStatistic = StatisticalMap3D(dimX, dimY, dimZ);

        //And a 4d map for nuisance residuals vectors in every voxel
        StatisticalMap4D epsilonZetas(dimX, dimY, dimZ, N);

        //Computing utility matrices
        double epsilon = std::numeric_limits<double>::epsilon();
        Eigen::MatrixXd Mplus = pseudoInverse(M, epsilon);
        Eigen::MatrixXd Zplus = pseudoInverse(Z, epsilon);
        Eigen::MatrixXd ResidualFormingMatrixZ = (I - Z*Zplus);
        Eigen::MatrixXd ResidualFormingMatrixM = (I - M*Mplus);

        //Setting omp variables
        int max_num_threads = omp_get_num_procs();
        omp_set_num_threads(max_num_threads);

        //Computing statistics on original model
        #pragma omp parallel for
        for(int v = 0; v < numVoxels; v++){
            epsilonZetas[v] = ResidualFormingMatrixZ * Y[v];
            Eigen::VectorXd phiv = Mplus*epsilonZetas[v];
            Eigen::VectorXd epsilonv = ResidualFormingMatrixM*epsilonZetas[v];
            toReturn[index].originalStatistic[v] = pivotal(phiv, epsilonv, M, c, s, VGS);
        }

        if(useTfce)
            toReturn[index].originalStatistic.tfce();

        toReturn[index].maxDistribution = std::vector<float>(actualPermutationSize);


        #pragma omp parallel for
        for(int j = 0; j < actualPermutationSize; j++){
            std::vector<int> currentPerm;
            #pragma omp critical
            {
                if(j != 0){
                    if(!exhaustively){
                        if(EE)
                            t.randomShuffle();
                        if(ISE)
                            t.randomSignFlip();
                    }
                    else{
                        //both hypothesis
                        if(EE && ISE){
                            if(!t.signFlipping()){
                                t.resetTreeSignState();
                                t.LAlgorithm();
                            }
                        }
                        //error only exchangeable
                        else if(EE){
                            t.LAlgorithm();
                        }
                        //error indipendent and simmetric
                        else{
                            t.signFlipping();
                        }
                    }
                }
                currentPerm = t.getSignVector();
            }
            Eigen::MatrixXd Pj = buildShufflingMatrix(currentPerm);
            Eigen::MatrixXd Mj = Pj*M;
            Eigen::MatrixXd Mjplus = pseudoInverse(Mj, epsilon);
            Eigen::MatrixXd ResidualFormingMatrixMj = (I - Mj*Mjplus);

            //Initialize values to find max statistic value in all permutations
            StatisticalMap3D permutedStatistic(dimX, dimY, dimZ);

            //Computing statistic on the permuted model
            for(int v = 0; v < numVoxels; v++){
                Eigen::VectorXd phijv = Mjplus*epsilonZetas[v];
                Eigen::VectorXd epsilonjv = ResidualFormingMatrixMj*epsilonZetas[v];
                permutedStatistic[v] = pivotal(phijv, epsilonjv, Mj, c, s, VGS);
                if(permutedStatistic[v] >= toReturn[index].originalStatistic[v]){
                    toReturn[index].uncorrected[v] += 1;
                }
            }

            if(useTfce)
                permutedStatistic.tfce();

            //Find the maximum
            float maxTj = permutedStatistic[0];
            for(int v = 1; v < numVoxels; v++){
                if(permutedStatistic[v] > maxTj){
                    maxTj = permutedStatistic[v];
                }
            }

            //NOTE: Instead of computing pvalues in this way
            //a vector of maxes can be used to assest inference
            toReturn[index].maxDistribution[j] = maxTj;

            //Using the maximum to compute FWER
            for(int v = 0; v < numVoxels; v++){
                if(maxTj >= toReturn[index].originalStatistic[v]){
                    toReturn[index].corrected[v] += 1;
                }
            }
        }
        t.resetTreePermutationState();
        t.resetTreeSignState();
        toReturn[index].uncorrected /= actualPermutationSize;
        toReturn[index].corrected /= actualPermutationSize;
        std::sort(toReturn[index].maxDistribution.begin(), toReturn[index].maxDistribution.end());
        //maximal statistic is now sorted from the lowest to the highest, we need the opposite
        std::reverse(toReturn[index].maxDistribution.begin(), toReturn[index].maxDistribution.end());
        index++;
    }
    return toReturn;
}
