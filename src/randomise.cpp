#include "randomise.h"
#include "permutationtree.h"
#include "matrices.h"
#include "mystat.h"
#include <random>
#include <tuple>

Randomise::Randomise()
{

}

//PARTITIONING NOTE
// Partion the design matrix M basing on the contrast C as indicated on the paper
//X contains the design for the regressors of interest and Z for nuisance variable
//Variables dimensionality:
//M is N x r
//C is r x s
//X is N x s
//Z is N x (r-s)
//with 1 <= s <=r

//NOTE: Question with no answer: what happens in the partitioning when there are no nuisance variables?
//We'll only have the answer with the tests

//Model for one contrast
RandomiseResult Randomise::randomise(StatisticalMap4D& Y, Eigen::MatrixXd& M, Eigen::MatrixXd& C, std::vector<std::vector<int>>& MultyRowArray, float (*pivotal)(Eigen::VectorXd &, Eigen::VectorXd &, Eigen::MatrixXd &, Eigen::MatrixXd &, int, std::vector<int> &), bool EE, bool ISE, int J){
    //Building the permutation tree
    PermutationTree t(MultyRowArray);
    t.initializeBinaryCounters();
    t.initializeThreeColsArray();

    //Storing number of observations for convinieance
    int N = Y.getNumMaps();

    //Partitioning the model
    Eigen::MatrixXd D = (M.transpose() * M).inverse();
    Eigen::MatrixXd Ctrasp = C.transpose();
    Eigen::MatrixXd X = M*D*C*((Ctrasp*D*C).inverse());
    //"Cu is a matrix whose columns span in the null space of C"
    Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
    int s = lu.rank();
    Eigen::MatrixXd Cu = lu.kernel();
    Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse());
    Eigen::MatrixXd Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());


    //"For semplicity, replace M"
    M(X.rows(), X.cols()+Z.cols());
    M << X, Z;

    //Storing the identity matrix for convenience
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(N, N);

    //Computing the # number of permutations
    int Jmax = t.calculatePermutations(X, EE, ISE);

    //Computing the minimum set of VGS
    std::vector<int> VGS = t.getMinimumSetOfVarianceGroups();

    //Initializing shufflings vectors
    std::vector<Eigen::MatrixXd> shufflings;
    std::vector<Eigen::MatrixXd> permutations;
    std::vector<Eigen::MatrixXd> signflippings;
    std::vector<Eigen::MatrixXd> * vectorToUse;

    //NOTE: if J >= Jmax then we're going exhaustively

    if(ISE){
        if(J >= Jmax){
            //in both cases, first iteration ensures the including of the original
            //model
            do{
                std::vector<int> currentPerm = t.getSignVector();
                Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
                signflippings.push_back(P);
            }while(t.signFlipping());
        }else{
            for(int i = 0; i < J; i++){
                std::vector<int> currentPerm = t.getSignVector();
                Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
                signflippings.push_back(P);
                t.randomSignFlip();
            }
        }
        vectorToUse = &signflippings;
        t.resetTreeSignState();
    }
    if(EE){
        if(J >= Jmax){
            //If we're going exhaustivly, then we must assure
            //that the tree is ready for L Algorithm.
            t.reverseLAlgorithm();
            //in both cases, first iteration ensures the including of the original model
            do{
                std::vector<int> currentPerm = t.getPermutationVector();
                Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
                permutations.push_back(P);
            }while(t.LAlgorithm());
        }else{
            for(int i = 0; i < J; i++){
                std::vector<int> currentPerm = t.getSignVector();
                Eigen::MatrixXd P = buildShufflingMatrix(currentPerm);
                permutations.push_back(P);
                t.randomShuffle();
            }
        }
        vectorToUse = &permutations;
        t.resetTreePermutationState();
    }
    if(EE && ISE){
        int numOfSignFlippings = signflippings.size();
        int numOfPermutations = permutations.size();
        if(J >= Jmax){
            for(int i = 0; i < numOfPermutations; i++){
                for(int j = 0; i < numOfSignFlippings; j++){
                    shufflings.push_back(permutations[i]*signflippings[j]);
                }
            }
        }else{
            //ensure that original model is added in the random drawing case
            shufflings.push_back(I);
            //setting up uniform distributions for random drawing
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> d1(0, numOfPermutations-1);
            std::uniform_int_distribution<int> d2(0, numOfSignFlippings-1);
            for(int i = 1; i < J; i++){
                shufflings.push_back(permutations[d1(gen)]*signflippings[d2(gen)]);
            }
        }
        vectorToUse = &shufflings;
    }

    //Now, a vector of shufflings is available through the variable
    //vector to use. Let's risolve the original model.

    //First, we get the number of voxels
    int numVoxels = Y.getNumVoxels();

    //Then, we inizialize counters for uncorrected and corrected pvalues
    RandomiseResult toReturn;
    toReturn.corrected = StatisticalMap3D(numVoxels);
    toReturn.uncorrected = StatisticalMap3D(numVoxels);

    //Also, we inizialize a 3dmap to store the statistic on the
    //original permutation
    toReturn.originalStatistic = StatisticalMap3D(numVoxels);

    //And a 4d map for nuisance residuals vectors in every voxel
    StatisticalMap4D epsilonZetas(numVoxels, N);

    //Computing utility matrices
    Eigen::MatrixXd Mplus = pseudoInverse(M);
    Eigen::MatrixXd ResidualFormingMatrixZ = (I - Z*pseudoInverse(Z));
    Eigen::MatrixXd ResidualFormingMatrixM = (I - M*Mplus);

    //Computing statistics on original model
    for(int v = 0; v < numVoxels; v++){
        epsilonZetas[v] = ResidualFormingMatrixZ * Y[v];
        Eigen::VectorXd phiv = Mplus*epsilonZetas[v];
        Eigen::VectorXd epsilonv = ResidualFormingMatrixM*epsilonZetas[v];
        toReturn.originalStatistic[v] = pivotal(phiv, epsilonv, M, C, s, VGS);
    }

    //Computing statistics on permuted models

    //How many permutations are we using
    int actualPermutationSize = vectorToUse->size();

    for(int j = 0; j < actualPermutationSize; j++){
        //For each permutation, we must calculate
        //utility matrices
        Eigen::MatrixXd Pj = vectorToUse->at(j);
        Eigen::MatrixXd Mj = Pj*M;
        Eigen::MatrixXd Mjplus = pseudoInverse(Mj);
        Eigen::MatrixXd ResidualFormingMatrixMj = (I - Mj*Mjplus);

        //Initialize values to find max statistic value in all permutations
        bool firstMaxFound = false;
        float maxTj = 0;

        //Computing statistic on the permuted model
        for(int v = 0; v < numVoxels; v++){
            Eigen::VectorXd phijv = Mplus*epsilonZetas[v];
            Eigen::VectorXd epsilonjv = ResidualFormingMatrixMj*epsilonZetas[v];
            float tjv = pivotal(phijv, epsilonjv, Mj, C, s, VGS);
            if(tjv >= toReturn.originalStatistic[v])
                toReturn.uncorrected[v] += 1;
            if(!firstMaxFound){
                firstMaxFound = true;
                maxTj = tjv;
            }
            else{
                if(tjv > maxTj)
                    maxTj = tjv;
            }
        }

        for(int v = 0; v < numVoxels; v++){
            if(maxTj >= toReturn.originalStatistic[v])
                toReturn.corrected[v] += 1;
        }
    }

    toReturn.uncorrected /= actualPermutationSize;
    toReturn.corrected /= actualPermutationSize;

    return toReturn;
}
