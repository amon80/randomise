#include "permutationtree.h"
#include "permutationtreeblock.h"
#include "mymath.h"

//-------------UTILITY FUNCTIONS------------


int findMax(std::vector<int>& v, PermutationTreeBlock * block){
    int n = block->getIndicesSize();
    int max = abs(v[block->getIndex(0)]);
    for(int i = 1; i < n; i++){
        int currentNumber = abs(v[block->getIndex(i)]);
        if(currentNumber > max)
            max = currentNumber;
    }
    return max;
}

std::vector<int> findIndices(std::vector<int>& row, int block_number, PermutationTreeBlock * block){
    std::vector<int> indices;
    int n = block->getIndicesSize();
    for(int i = 0; i < n; i++){
        if(abs(row[block->getIndex(i)]) == block_number)
            indices.push_back(block->getIndex(i));
    }
    return indices;
}

void buildTreeRecursively(PermutationTreeBlock * block, unsigned int currentRow, std::vector<std::vector<int>>& multyRowArray){
    //base case
    if(currentRow == multyRowArray.size()-1){
        int n = block->getIndicesSize();
        for(int i = 0; i < n; i++){
            //last row are actual observations, so indices don't make really sense
            PermutationTreeBlock * element = new PermutationTreeBlock(false);
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
        PermutationTreeBlock * sonI = new PermutationTreeBlock(indices, permutable);
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

bool confrontBranch(PermutationTreeBlock * b1, PermutationTreeBlock * b2, Eigen::MatrixXd &X){
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
        if(!confrontBranch(b1->getSon(i), b2->getSon(i), X))
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
    numleaves = n;
    std::vector<int> indices(n);
    for(int i = 0; i < n; i++){
        indices[i] = i;
    }
    root = new PermutationTreeBlock(indices, permutable);
    buildTreeRecursively(root, 1, multyRowArray);
}


void PermutationTree::initializeThreeColsArray(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    //base case is the same of confrontbranch function, so be careful
    if(numSons == 0)
        return;
    block->initializeThreeColsArray();
    for(int i = 0; i < numSons; i++)
        initializeThreeColsArray(block->getSon(i));
}

void PermutationTree::initializeBinaryCounters(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return;
    block->initializeBinaryCounter();
    for(int i = 0; i < numSons; i++)
        initializeBinaryCounters(block->getSon(i));
}



//before calling this function, be sure to have initialized the three cols array for each node
//in the tree
int PermutationTree::calculatePermutations(Eigen::MatrixXd &X, bool EE, bool ISE, PermutationTreeBlock *block){
    int numPermutation = 1;

    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    bool permutable = block->isPermutable();

    if(numSons == 0)
        return numPermutation;

    if(ISE){
        if(permutable)
            numPermutation <<= numSons;
    }
    if(EE){
        if(permutable){
            //in the EE hypothesis, if block is permutable, a check for equal branches
            //(same rows of the design matrix) must be made.

            //either if branches are equal or not, the three column array for
            //building the permutation matrix should be filled here
            //so it can be used to find unique branches and how many times they repeat
            int branch_id = 0;
            ThreeColsArray t = block->getThreeColsArray();
            for(int i = 0; i < numSons; i++){
                if(t(0,i) == -1){
                    t(0,i) = branch_id++;
                    for(int j = i + 1; j < numSons; j++)
                        if(confrontBranch(block->getSon(i), block->getSon(j), X))
                            t(0,j) = t(0,i);
                }
            }
            //At this point, there are exactly branch_id different branches
            //if this numbers is equal to the number of sons, then all
            //the branches are different
            numPermutation *= fact(numSons);
            if(branch_id < numSons){
                for(int i = 0; i < branch_id; i++){
                    int timesThatBranchIRepeats = 0;
                    for(int j = 0; j < numSons; j++)
                        if(t(0,j) == i)
                            timesThatBranchIRepeats++;
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

std::vector<int> PermutationTree::getPermutationVector(PermutationTreeBlock *block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return (std::vector<int>(1, block->getValue()));
    std::vector<int> toReturn;
    for(int i = 0; i < numSons; i++){
        std::vector<int> toReturnI = getPermutationVector(block->getSon(i));
        for(int a: toReturnI)
            toReturn.push_back(a);
    }
    return toReturn;
}

std::vector<int> PermutationTree::getSignVector(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return (std::vector<int>(1, block->getValue()));
    std::vector<int> toReturn;
    BinaryString counter = block->getBinaryCounter();
    for(int i = 0; i < numSons; i++){
        std::vector<int> toReturnI = getSignVector(block->getSon(i));
        for(int a: toReturnI){
            if(counter[i] == 1)
                toReturn.push_back(-a);
            else
                toReturn.push_back(a);
        }
    }
    return toReturn;
}


int PermutationTree::getNumLeaves(){
    return numleaves;
}

bool PermutationTree::isLAlgorithmApplicable(){

}

bool PermutationTree::areThereOtherSignFlipping(){

}

void PermutationTree::LAlgorithm(){

}

void PermutationTree::signFlipping(){

}

