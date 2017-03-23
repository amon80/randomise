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
    //-1 is because elements in the leaves are numbered from
    //1...nleaves, while the matrix has rows
    //0...nleaves-1
    if(b1sons == 0){
        int row1 = b1->getValue();
        int row2 = b2->getValue();
        if(confrontRows(X, row1-1, row2-1))
            return true;
        else
            return false;
    }
    //recursion case
    for(int i = 0; i < b1sons; i++)
        if(!confrontBranch(b1->getSon(i), b2->getSon(i), X))
            return false;
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
    for(int i = 0; i < n; i++)
        indices[i] = i;
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

    if(ISE)
        if(permutable)
            numPermutation <<= numSons;
    if(EE){
        if(permutable){
            //in the EE hypothesis, if block is permutable, a check for equal branches
            //(same rows of the design matrix) must be made.

            //either if branches are equal or not, the three column array for
            //building the permutation matrix should be filled here
            //so it can be used to find unique branches and how many times they repeat
            int branch_id = 0;
            for(int i = 0; i < numSons; i++){
                if(block->getThreeColsArray().at(0,i) == -1){
                    block->getThreeColsArray().at(0,i) = branch_id++;
                    for(int j = i + 1; j < numSons; j++)
                        if(confrontBranch(block->getSon(i), block->getSon(j), X))
                            block->getThreeColsArray().at(0,j) = block->getThreeColsArray().at(0,i);
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
                        if(block->getThreeColsArray().at(0,j) == i)
                            timesThatBranchIRepeats++;
                    numPermutation /= fact(timesThatBranchIRepeats);
                }
            }
        }
    }

    for(int i = 0; i < numSons; i++)
        numPermutation *= calculatePermutations(X, EE, ISE, block->getSon(i));

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

std::vector<int> PermutationTree::getMinimumSetOfVarianceGroups(PermutationTreeBlock * block, int counter){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    //base case: leaf
    if(numSons == 0)
        return (std::vector<int>(1, counter));
    //check if its permutable?
    std::vector<int> toReturn;
    for(int i = 0; i < numSons; i++){
        std::vector<int> toReturnI = getMinimumSetOfVarianceGroups(block->getSon(i), counter);
        if(!block->isPermutable())
            counter++;
        for(int a: toReturnI)
            toReturn.push_back(a);
    }
    return toReturn;
}



int PermutationTree::getNumLeaves(){
    return numleaves;
}

bool PermutationTree::LAlgorithm(PermutationTreeBlock * block, std::vector<PermutationTreeBlock*> * alreadyVisited){
    if(block == nullptr){
        block = root;
        alreadyVisited = new std::vector<PermutationTreeBlock*>(0);
    }
    //base case #1: block is not permutable. In this case it shall not be added to the list
    if(!block->isPermutable())
        return false;
    //base case #2: block is permutable, let's check if L algorithm is appliable
    //"The tree is swept from the top node [...] stopping when a single pairwise permutation of branches can be performed"
    if(block->isLAlgorithmApplicable()){
        block->applyLAlgorithm();
        //"The branches are then swapped, all the previous visited nodes already visited
        //are reset back to the original, unpermuted state"
        int n = alreadyVisited->size();
        for(int i = 0; i < n; i++){
            PermutationTreeBlock * currentNodeToReset = alreadyVisited->at(i);
            currentNodeToReset->resetNodePermutationState();
        }
        delete alreadyVisited;
        return true;
    }
    //recursion case - if the function arrives here then the block is permutable, but has reached is last possible
    //lexicograph permutation. So, it shall be added to list of already visited nodes.
    alreadyVisited->push_back(block);
    int numSons = block->getNumSons();
    bool oneOfTheSonsIsPermutable = false;
    for(int i = 0; i < numSons; i++){
        if(LAlgorithm(block->getSon(i), alreadyVisited)){
            oneOfTheSonsIsPermutable = true;
            break;
        }
    }
    if(oneOfTheSonsIsPermutable)
        return true;
    else{
        if(block == root)
            delete alreadyVisited;
        return false;
    }
}

bool PermutationTree::signFlipping(PermutationTreeBlock * block, std::vector<PermutationTreeBlock*> * alreadyVisited){
    if(block == nullptr){
        block = root;
        alreadyVisited = new std::vector<PermutationTreeBlock*>(0);
    }
    //base case #1: block is not permutable. In this case it shall not be added to the list
    if(!block->isPermutable())
        return false;
    //base case #2: block is permutable, let's check if counter is incrementable
    //"The tree is swept from the top node [...] stopping when a single sign flipping can be performed
    if(block->isIncrementable()){
        block->incrementCounter();
        //"The counter is incremented all the previous visited nodes already visited
        //are reset back to the original, non sign flipped state"
        int n = alreadyVisited->size();
        for(int i = 0; i < n; i++){
            PermutationTreeBlock * currentNodeToReset = alreadyVisited->at(i);
            currentNodeToReset->resetCounter();
        }
        delete alreadyVisited;
        return true;
    }
    //recursion case - if the function arrives here then the block is permutable, but his counter has reached its last possible
    //state. So, it shall be added to list of already visited nodes.
    alreadyVisited->push_back(block);
    int numSons = block->getNumSons();
    bool oneOfTheSonsIsSignFlippable = false;
    for(int i = 0; i < numSons; i++){
        if(signFlipping(block->getSon(i), alreadyVisited)){
            oneOfTheSonsIsSignFlippable = true;
            break;
        }
    }
    if(oneOfTheSonsIsSignFlippable)
        return true;
    else{
        if(block == root)
            delete alreadyVisited;
        return false;
    }
}

void PermutationTree::randomShuffle(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return;
    if(block->isPermutable())
        block->randomSwapSons();
    for(int i = 0; i < numSons; i++)
        randomShuffle(block->getSon(i));
    return;
}

void PermutationTree::randomSignFlip(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return;
    if(block->isPermutable())
       block->setRandomCounter();
    for(int i = 0; i < numSons; i++)
        randomSignFlip(block->getSon(i));
    return;
}

void PermutationTree::resetTreePermutationState(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return;
    if(block->isPermutable())
        block->resetNodePermutationState();
    for(int i = 0; i < numSons; i++)
        resetTreePermutationState(block->getSon(i));
}

void PermutationTree::resetTreeSignState(PermutationTreeBlock * block){
    if(block == nullptr)
        block = root;
    int numSons = block->getNumSons();
    if(numSons == 0)
        return;
    if(block->isPermutable())
        block->resetCounter();
    for(int i = 0; i < numSons; i++)
        resetTreeSignState(block->getSon(i));
}


