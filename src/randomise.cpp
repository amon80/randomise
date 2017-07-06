#include "randomise.h"
#include "permutationtree.h"
#include "matrices.h"
#include "tfce.h"
#include "mystat.h"
#include "mymath.h"
#include <random>
#include <limits>
#include <algorithm>
#include <vector>
#include <omp.h>

std::vector<RandomiseResult> randomise(StatisticalMap4D& Y, Eigen::MatrixXd& M, std::vector<Eigen::MatrixXd>& C, MultyRowArray &a, float (*pivotal)(Eigen::VectorXd& phi, Eigen::VectorXd& epsilon, Eigen::MatrixXd& partitionedM, Eigen::MatrixXd& unpartitionedM, Eigen::MatrixXd& Pj, Eigen::MatrixXd& R, Eigen::MatrixXd& C, int s, std::vector<int>& VGS), bool useTfce, float E, float H, float dh, Connectivity3D * conn, bool EE, bool ISE, int J, float alpha, int *performed_perm, int *total_perm, int *contrast, int * maxNumberPermutations){
    //Storing number of observations for convinieance
    int N = Y.getNumMaps();

    //Initializing the vector of results
    std::vector<RandomiseResult> toReturn(C.size());

    //Initializing permutations counters variables
    (*performed_perm) = 0;
    (*total_perm) = 0;

    int index = 0;
    for(Eigen::MatrixXd c: C){
        //NOTE: This has to be done here
        //since the partitioning changes with each
        //contrast.
        //Building the permutation tree
        PermutationTree t(a);
        t.initializeBinaryCounters();
        t.initializeThreeColsArray();

        //Copy the original design matrix
        //NOTE:This is necessary since MCopy will be replaced by the partitioning
        //The original model is also needed by the G statistic
        Eigen::MatrixXd MCopy = M;

        //Storing the identity matrix for convenience
        Eigen::MatrixXd I = Eigen::MatrixXd::Identity(N, N);

        //Partitioning the model and computing the rank of the contrast
        PartitioningResult partitioning = partitionModel(M, c, I);
        Eigen::MatrixXd X = partitioning.X;
        Eigen::MatrixXd Z = partitioning.Z;
        int s = c.cols();
        int r = c.rows();

        //"For semplicity, replace M"
        if(r != s){
            Eigen::MatrixXd tmp(X.rows(), X.cols()+Z.cols());
            tmp << X, Z;
            MCopy = tmp;
        }
        else{
            MCopy = X;
        }

        //Computing the max number of permutations
        int Jmax = t.calculatePermutations(X, EE, ISE);
        (*maxNumberPermutations) = Jmax;

        //Computing the minimum set of VGS
        std::vector<int> VGS = t.getMinimumSetOfVarianceGroups();

        //NOTE: if J >= Jmax then we're going exhaustively
        bool exhaustively = false;
        int actualPermutationSize = 0;
        if(J == -1 || J >= Jmax){
            exhaustively = true;
            actualPermutationSize = Jmax;
            t.reverseLAlgorithm();
        }else{
            actualPermutationSize = J;
        }
        (*total_perm) = actualPermutationSize;

        //Let's risolve the original model.
        //First, we get the informations that we need from the 4D map
        int numVoxels = Y.getNumVoxels();
        int dimX = Y.getDimX();
        int dimY = Y.getDimY();
        int dimZ = Y.getDimZ();

        //Then, we inizialize counters for uncorrected and corrected pvalues
        toReturn[index].corrected = StatisticalMap3D(dimX, dimY, dimZ);
        toReturn[index].uncorrected = StatisticalMap3D(dimX, dimY, dimZ);
		//Adding +1 so we don't need to recompute statistic on original permutation
		toReturn[index].uncorrected.applyOperation(add, 1);
		toReturn[index].corrected.applyOperation(add, 1);

        //Also, we inizialize a 3dmap to store the statistic on the
        //original permutation
        toReturn[index].originalStatistic = StatisticalMap3D(dimX, dimY, dimZ);

        //And a 4d map for nuisance residuals vectors in every voxel
        StatisticalMap4D epsilonZetas(dimX, dimY, dimZ, N);

        //Computing utility matrices
        double epsilon = std::numeric_limits<double>::epsilon();
        Eigen::MatrixXd Mplus = pseudoInverse(MCopy, epsilon);
        Eigen::MatrixXd Zplus = pseudoInverse(Z, epsilon);
        Eigen::MatrixXd ResidualFormingMatrixZ = (I - Z*Zplus);
        Eigen::MatrixXd ResidualFormingMatrixM = (I - MCopy*Mplus);

		//Setting up the statistic
		float(*statisticToUse)(Eigen::VectorXd&, Eigen::VectorXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, Eigen::MatrixXd&, int, std::vector<int>&) = nullptr;
        if (pivotal == FStatistic && s == 1)
			statisticToUse = TStatistic;
		else
			statisticToUse = pivotal;

        //Setting omp variables
        int max_num_threads = omp_get_num_procs();
        omp_set_num_threads(max_num_threads);

        //Computing statistics on original model
        #pragma omp parallel for
        for(int v = 0; v < numVoxels; v++){
            epsilonZetas[v] = ResidualFormingMatrixZ * Y[v];
            Eigen::VectorXd phiv = Mplus*epsilonZetas[v];
            Eigen::VectorXd epsilonv = ResidualFormingMatrixM*epsilonZetas[v];
            toReturn[index].originalStatistic[v] = statisticToUse(phiv, epsilonv, MCopy, M, I, ResidualFormingMatrixM, c, s, VGS);
        }

        if(useTfce)
            tfce(toReturn[index].originalStatistic, E, H, dh, conn);

        toReturn[index].maxDistribution = std::vector<float>(actualPermutationSize);
		toReturn[index].exectuedPermutations = std::vector<std::vector<int>>(actualPermutationSize);
		toReturn[index].exectuedPermutations[0] = t.getSignVector();

		//Computing and storing max of the original model
		float maxT0 = toReturn[index].originalStatistic[0];
		for (int v = 1; v < numVoxels; v++) {
			if (toReturn[index].originalStatistic[v] > maxT0) {
				maxT0 = toReturn[index].originalStatistic[v];
			}
		}
		toReturn[index].maxDistribution[0] = maxT0;
		(*performed_perm) += 1;

        #pragma omp parallel for
        for(int j = 1; j < actualPermutationSize; j++){
            std::vector<int> currentPerm;
            #pragma omp critical
            {
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
				currentPerm = t.getSignVector();
            }
			toReturn[index].exectuedPermutations[j] = currentPerm;
            Eigen::MatrixXd Pj = buildShufflingMatrix(currentPerm);
            Eigen::MatrixXd Mj = Pj*MCopy;
            Eigen::MatrixXd Mjplus = pseudoInverse(Mj, epsilon);
            Eigen::MatrixXd ResidualFormingMatrixMj = (I - Mj*Mjplus);

            //Initialize values to find max statistic value in all permutations
            StatisticalMap3D permutedStatistic(dimX, dimY, dimZ);

            //Computing statistic on the permuted model
            for(int v = 0; v < numVoxels; v++){
                Eigen::VectorXd phijv = Mjplus*epsilonZetas[v];
                Eigen::VectorXd epsilonjv = ResidualFormingMatrixMj*epsilonZetas[v];
                permutedStatistic[v] = statisticToUse(phijv, epsilonjv, Mj, M, Pj, ResidualFormingMatrixMj, c, s, VGS);
            }

            //First, apply TFCE (if requested)
            if(useTfce)
                tfce(permutedStatistic, E, H, dh, conn);

            //Then, increment uncorrected p-values counters
            for(int v = 0; v < numVoxels; v++){
                if(permutedStatistic[v] >= toReturn[index].originalStatistic[v]){
                    #pragma omp atomic
                        toReturn[index].uncorrected[v] += 1;
                }
            }

            //Find the maximum and saving it
            float maxTj = permutedStatistic[0];
            for(int v = 1; v < numVoxels; v++){
                if(permutedStatistic[v] > maxTj){
                    maxTj = permutedStatistic[v];
                }
            }
            toReturn[index].maxDistribution[j] = maxTj;

            //Using the maximum to compute FWER
            for(int v = 0; v < numVoxels; v++){
                if(maxTj >= toReturn[index].originalStatistic[v]){
                    #pragma omp atomic
                        toReturn[index].corrected[v] += 1;
                }
            }

            //Updating counter
            #pragma omp atomic
                (*performed_perm) += 1;
        }
        //finished the computation for current contrast
        //NOTE: Single threaded from here

        //OPTIONAL
        //t.resetTreePermutationState();
        //t.resetTreeSignState();
        toReturn[index].performedPermutations = actualPermutationSize;
        if(actualPermutationSize > 0){
            toReturn[index].uncorrected /= actualPermutationSize;
            toReturn[index].corrected /= actualPermutationSize;
            std::sort(toReturn[index].maxDistribution.begin(), toReturn[index].maxDistribution.end());
            //maximal statistic is now sorted from the lowest to the highest, we need the opposite
            std::reverse(toReturn[index].maxDistribution.begin(), toReturn[index].maxDistribution.end());
            toReturn[index].criticalThreshold = toReturn[index].maxDistribution[floor(alpha*toReturn[index].performedPermutations)];
        }
		index++;
        (*contrast)++;
		(*performed_perm) = 0;
    }
    return toReturn;
}
