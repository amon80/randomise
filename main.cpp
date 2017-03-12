#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

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
bool confrontRows(Eigen::MatrixXd& X, int row1, int row2){
    int ncols = X.cols();
    for(int i = 0; i < ncols; i++){
        if(X(row1, i) != X(row2, i))
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
        int row1 = block1[i];
        int row2 = block2[i];
        if(!confrontRows(X, row1, row2))
            return false;
    }
    return true;
}


//This functions finds all the blocks and stores them in a convinient manner
//For every block i, blocks[i] contains the indices of the rows that compose the block
//This works since blocks are numbered from 0 to numBlocks-1
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
//1) If the last item repeats one of the previous, it has already been counted.
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
                //compute permutation for such block here
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
    Eigen::MatrixXd X(6,2);

    X(0, 0) = 1;
    X(0, 1) = 2;
    X(1, 0) = 3;
    X(1, 1) = 4;
    X(2, 0) = 5;
    X(2, 1) = 6;

    X(3, 0) = 1;
    X(3, 1) = 2;
    X(4, 0) = 3;
    X(4, 1) = 4;
    X(5, 0) = 5;
    X(5, 1) = 6;

    std::vector<int> b1(6,0);

    b1[0] = 0;
    b1[1] = 0;
    b1[2] = 0;
    b1[3] = 0;
    b1[4] = 0;
    b1[5] = 0;

    std::vector<std::vector<int>> blocks1 = findBlocks(b1);

    std::vector<int> b2(6,0);

    b2[0] = 0;
    b2[1] = 0;
    b2[2] = 0;
    b2[3] = 1;
    b2[4] = 1;
    b2[5] = 1;

    std::vector<std::vector<int>> blocks2 = findBlocks(b2);

    std::vector<int> b3(6,0);

    b3[0] = 0;
    b3[1] = 1;
    b3[2] = 2;
    b3[3] = 0;
    b3[4] = 1;
    b3[5] = 2;

    std::vector<std::vector<int>> blocks3 = findBlocks(b3);

    std::vector<int> b4(6,0);

    b4[0] = 0;
    b4[1] = 0;
    b4[2] = 1;
    b4[3] = 2;
    b4[4] = 2;
    b4[5] = 3;

    std::vector<std::vector<int>> blocks4 = findBlocks(b4);

    int maxShufflings1 = calculateMaxShufflings(X, blocks1, true, true, true);
    int maxShufflings2 = calculateMaxShufflings(X, blocks2, true, true, true);
    int maxShufflings3 = calculateMaxShufflings(X, blocks3, true, true, true);
    int maxShufflings4 = calculateMaxShufflings(X, blocks4, true, true, true);


    return 0;
}
