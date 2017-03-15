#include "permutationtree.h"
#include "treeblock.h"
#include "mymath.h"

//-------------UTILITY FUNCTIONS------------


int findMax(std::vector<int>& v, TreeBlock * block){
    int n = block->getIndicesSize();
    int max = abs(v[block->getIndex(0)]);
    for(int i = 1; i < n; i++){
        int currentNumber = abs(v[block->getIndex(i)]);
        if(currentNumber > max)
            max = currentNumber;
    }
    return max;
}

std::vector<int> findIndices(std::vector<int>& row, int block_number, TreeBlock * block){
    std::vector<int> indices;
    int n = block->getIndicesSize();
    for(int i = 0; i < n; i++){
        if(abs(row[block->getIndex(i)]) == block_number)
            indices.push_back(block->getIndex(i));
    }
    return indices;
}

void buildTreeRecursively(TreeBlock * block, unsigned int currentRow, std::vector<std::vector<int>>& multyRowArray){
    //base case
    if(currentRow == multyRowArray.size()-1){
        int n = block->getIndicesSize();
        for(int i = 0; i < n; i++){
            //last row are actual observations, so indices don't make really sense
            TreeBlock * element = new TreeBlock(false);
            element->setValue(multyRowArray[currentRow][block->getIndex(i)]);
            block->addSon(element);
        }
        return;
    }
    //recursion
    int numSons = findMax(multyRowArray[currentRow], block);
    //for(int i = 0; i < numSons; i++)
    //of course depends on how block are enumerated
    //here is assumed from 1 to numSons(included)
    for(int i = 1; i <= numSons; i++){
        std::vector<int> indices = findIndices(multyRowArray[currentRow], i, block);
        bool permutable = false;
        if(multyRowArray[currentRow][indices[0]] > 0)
            permutable = true;
        if(indices.size() == 1)
            permutable = false;
        TreeBlock * sonI = new TreeBlock(indices, permutable);
        block->addSon(sonI);
        buildTreeRecursively(sonI, currentRow+1, multyRowArray);
    }
}

bool confrontRows(Eigen::MatrixXd& X, int row1, int row2){
    int ncols = X.cols();

    for(int i = 0; i < ncols; i++){
        if(X(row1, i) != X(row2, i))
            return false;
    }
    return true;
}

bool confrontBranch(TreeBlock * b1, TreeBlock * b2, Eigen::MatrixXd &X){
    int b1sons = b1->getNumSons();
    int b2sons = b2->getNumSons();
    //to be equal, branches must have the same structure
    if(b1sons != b2sons)
        return false;
    //base case for recursion, using the matrix
    //NOT SURE, MAY BE CAUSE OF BUGS <- maybe fixed with 0
    if(b1sons == 0){
        int row1 = b1->getValue();
        int row2 = b2->getValue();
        if(confrontRows(X, row1, row2))
            return true;
        else
            return false;
    }
    //recursion case
    for(int i = 0; i < b1sons; i++){
        bool c = confrontBranch(b1->getSon(i), b2->getSon(i), X);
        if(!c)
            return false;
    }
    //if the function arrives here, means that all sub branches are equal, so the branches
    //are equal
    return true;
}


//----------------METHODS-----------------------

PermutationTree::PermutationTree(std::vector<std::vector<int>>& multyRowArray)
{
    bool permutable = false;
    if(multyRowArray[0][0] > 0)
        permutable = true;
    int n = multyRowArray[0].size();
    std::vector<int> indices(n);
    for(int i = 0; i < n; i++){
        indices[i] = i;
    }
    root = new TreeBlock(indices, permutable);
    buildTreeRecursively(root, 1, multyRowArray);
}


void PermutationTree::initializeThreeColsArray(TreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    //base case is the same of confrontbranch function, so be careful
    if(numSons == 0){
        return;
    }
    block->initializeThreeColsArray();
    for(int i = 0; i < numSons; i++){
        initializeThreeColsArray(block->getSon(i));
    }
}


//before calling this function, be sure to have initialized the three cols array for each node
//in the tree
int PermutationTree::calculatePermutations(Eigen::MatrixXd &X, bool EE, bool ISE, TreeBlock *block){
    int numPermutation = 1;

    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();

    if(numSons == 0)
        return numPermutation;

    if(ISE){
        if(block->isPermutable())
            numPermutation <<= numSons;
    }
    if(EE){
        if(block->isPermutable()){
            //in the EE hypothesis, if block is permutable, a check for equal branches
            //(same rows of the design matrix) must be made.

            //either if branches are equal or not, the three column array for
            //building the permutation matrix should be filled here
            //so it can be used to find unique branches and how many times they repeat
            int branch_id = 0;
            std::vector<int> firstRow = block->getArray(0);
            for(int i = 0; i < numSons; i++){
                if(firstRow[i] == -1){
                    firstRow[i] = branch_id++;
                    for(int j = i + 1; j < numSons; j++){
                        if(confrontBranch(block->getSon(i), block->getSon(j), X)){
                            firstRow[j] = firstRow[i];
                        }
                    }
                }
            }
            //At this point, there are exactly branch_id different branches
            //if this numbers is equal to the number of sons, then all
            //the branches are different
            numPermutation *= fact(numSons);
            if(branch_id < numSons){
                for(int i = 0; i < branch_id; i++){
                    int timesThatBranchIRepeats = 0;
                    for(int j = 0; j < numSons; j++){
                        if(firstRow[j] == i)
                            timesThatBranchIRepeats++;
                    }
                    numPermutation /= fact(timesThatBranchIRepeats);
                }
            }
        }
    }

    for(int i = 0; i < numSons; i++){
        numPermutation *= calculatePermutations(X, EE, ISE, block->getSon(i));
    }

    return numPermutation;
}
