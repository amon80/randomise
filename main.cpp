#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include "permutationtree.h"
#include "tests.h"

// Partion the design matrix M basing on the contrast C as indicated on the paper
//X contains the design for the regressors of interest and Z for nuisance variable
//Variables dimensionality:
//M is N x r
//C is r x s
//X is N x s
//Z is N x (r-s)
//with 1 <= s <=r
void partitionModel(Eigen::MatrixXd& M, Eigen::MatrixXd& C, Eigen::MatrixXd& X, Eigen::MatrixXd& Z){
   Eigen::MatrixXd D = (M.transpose() * M).inverse();
   Eigen::MatrixXd Ctrasp = C.transpose();

   X = M*D*C*((Ctrasp*D*C).inverse());
   //Cu is a matrix whose columns span in the null space of C
   Eigen::FullPivLU<Eigen::MatrixXd> lu(Ctrasp);
   Eigen::MatrixXd Cu = lu.kernel();
   Eigen::MatrixXd Cv = Cu - C*((Ctrasp*D*C).inverse());
   Z = M*D*Cv*((Cv.transpose()*D*Cv).inverse());
}


//This function confronts two rows
//Two rows are equal if they have the same elements
bool confrontRows(Eigen::MatrixXd& X, int row1Index, int row2Index){
    int ncols = X.cols();
    for(int i = 0; i < ncols; i++){
        if(X(row1Index, i) != X(row2Index, i))
            return false;
    }
    return true;
}

//This function confronts two blocks
//Two blocks are equal if:
//1) They have the same size
//2) Their rows are equal in order
bool confrontBlocks(Eigen::MatrixXd& X, std::vector<int>& block1, std::vector<int>& block2){
    if(block1.size() != block2.size())
        return false;
    int n = block1.size();
    for(int i = 0; i < n; i++){
        int row1Index = block1[i];
        int rowIndex = block2[i];
        if(!confrontRows(X, row1Index, rowIndex))
            return false;
    }
    return true;
}


//This functions finds all the blocks and stores them in a convinient manner
//For every block i, blocks[i] contains the indices of the rows that compose the block
//This works since blocks are numbered from 0 to numBlocks-1

//It is important to note that if the hypothesis is whole block exchangeability
//blocks must be composed by consecutive rows, and must be of the same size
//(otherwise permuting them is impossible)
std::vector<std::vector<int>> findBlocks(std::vector<int>& b){
    int numBlocks = *(std::max_element(b.begin(),b.end())) + 1;
    int numRows = b.size();
    std::vector<std::vector<int>> blocks(numBlocks);
    for(int i = 0; i < numBlocks; i++){
        for(int j = 0; j < numRows; j++){
            if(b[j] == i){
                blocks[i].push_back(j);
            }
        }
    }
    return blocks;
}

int fact(int n){
    int toReturn = 1;
    for(int i = 1; i<=n ; i++){
        toReturn *= i;
    }
    return toReturn;
}

//X is the N x s matrix obtained from the partitioning
//b is a vector of N integers. Each element in position i specifies the block of the i-th row of the matrix X
//block are enumerated from 0 to numBlock-1
//PB is a boolean flag that specifies if permutation are within block or whole block
//EE is a boolean flag that specifies if errors are exchangeable
//ISE is a boolean flag that specifies if errors are symmetric and indipendent

//NOTE: in both cases (PB and !PB) the for loop that finds repeated elements doesn't reach the last element.
//This works because there are only two cases possible:
//1) If the last item is equal to one of the previous, it has already been counted.
//2) If not, than it's count is equal to one, than the division is not necessary.
int calculateMaxShufflings(Eigen::MatrixXd& X, std::vector<std::vector<int>>& blocks, bool PB, bool EE, bool ISE){
    int numPermutation = 1;
    int numBlocks = blocks.size();
    int numRows = X.rows();

    if(!PB){//within-block exchangeability
        if(ISE){
            numPermutation <<= numRows;
        }
        if(EE){
            //check if there are repeated rows in each block
            for(int i = 0; i < numBlocks; i++){
                std::set<int> rowsToSkip;
                std::map<int, int> uniqueRows;
                int rowsInBlockI = blocks[i].size();
                for(int j = 0; j < rowsInBlockI-1; j++){
                    if(rowsToSkip.count(blocks[i][j]))
                        continue;
                    else
                        uniqueRows[blocks[i][j]] = 1;
                    for(int k = j+1; k < rowsInBlockI; k++){
                        bool areRowsEqual = confrontRows(X, blocks[i][j], blocks[i][k]);
                        if(areRowsEqual){
                            rowsToSkip.insert(blocks[i][k]);
                            uniqueRows[blocks[i][j]] += 1;
                        }
                    }
                }
                //now, for block i we have all the informations we need
                //compute the number of permutations for such block here
                numPermutation *= fact(rowsInBlockI);
                for(auto& row: uniqueRows){
                    int timesRepeated = row.second;
                    numPermutation /= fact(timesRepeated);
                }
            }
        }
    }else{//whole-block exchangeability
        if(ISE){
            numPermutation <<= numBlocks;
        }
        if(EE){
            std::set<int> blocksToSkip;
            std::map<int, int> uniqueBlocks;
            for(int i = 0; i < numBlocks-1; i++){
                if(blocksToSkip.count(i))
                    continue;
                else
                    uniqueBlocks[i] = 1;
                for(int j = i+1; j < numBlocks; j++){
                    bool areBlocksEqual = confrontBlocks(X, blocks[i], blocks[j]);
                    if(areBlocksEqual){
                        blocksToSkip.insert(j);
                        uniqueBlocks[i] += 1;
                    }
                }
           }
           numPermutation *= fact(numBlocks);
           for(auto& block: uniqueBlocks){
                int timesRepeated = block.second;
                numPermutation /= fact(timesRepeated);
           }
        }
    }
    return numPermutation;
}

//single contrast version
//ask for multi-contrast
template <typename T>
void randomise(T& Y, Eigen::MatrixXd& M, Eigen::MatrixXd& C, bool EE, bool ISE, int J, std::vector<int>b, bool PB){
    Eigen::MatrixXd X(M.rows(), C.cols());
    Eigen::MatrixXd Z(M.rows(), C.rows() - C.cols());

    partitionModel(M, C, X, Z);

    std::vector<std::vector<int>> blocks = findBlocks(b);
    int maxShufflings = calculateMaxShufflings(X, blocks, PB, EE, ISE);
    //TODO
}

int main(int argc, char *argv[])
{
    //test1(argc, argv)
    test2(argc, argv);
    //test3(argc, argv);
    //test4(argc, argv);
    //test5(argc, argv);
    //test6(argc, argv);


    return 0;
}
