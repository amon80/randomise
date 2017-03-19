#include "binarystring.h"
#include <random>

//friend functions
std::ostream & operator<<(std::ostream &os, const BinaryString& p){
    int i;
    for(i = 0; i < p.n_bits; i++){
        os << p.string[i];
    }
    return os;
}

void swap(BinaryString& first, BinaryString& second){
    using std::swap;

    swap(first.n_bits, second.n_bits);
    swap(first.string, second.string);

}

bool operator<(const BinaryString& first, const BinaryString& second){
    if(first.n_bits < second.n_bits)
        return true;
    for (int i = 0; i < first.n_bits; i++) {
        if (first.string[i] < second.string[i])
            return true;
        else if(first.string[i] > second.string[i])
            return false;
    }
    return false;
}

bool operator>(const BinaryString& first, const BinaryString& second){
    if(first.n_bits < second.n_bits)
        return false;
    for (int i = 0; i < first.n_bits; i++) {
        if (first.string[i] < second.string[i])
            return false;
        else if(first.string[i] > second.string[i])
            return true;
    }
    return false;
}

bool operator==(const BinaryString& first, const BinaryString& second){
    if(first.n_bits != second.n_bits)
        return false;
    for (int i = 0; i < first.n_bits; i++) {
        if (first.string[i] != second.string[i])
            return false;
    }
    return true;
}

//-----CONSTRUCTORS------------

BinaryString::BinaryString()
    :n_bits(0),
    string(nullptr)
{
}

BinaryString::BinaryString(int num_bits, int num_to_convert)
    :n_bits(num_bits),
    string(new int[num_bits])
{
    int mask = 1;
    for (int i = 0; i < num_bits; ++i) {
        if(num_to_convert & mask)
            string[num_bits-i-1] = 1;
        else
            string[num_bits-i-1] = 0;
        mask <<= 1;
    }
}


BinaryString::BinaryString(int num_bits, bool random)
    :n_bits(num_bits),
    string(new int[num_bits])
{
    reset();
    if(random)
        generateRandomly();
}

//----------- COPY SEMANTICS --------------
BinaryString::BinaryString(const BinaryString& rhs)
    :n_bits(rhs.n_bits),
    string(new int[rhs.n_bits])
{
	for(int i = 0; i < n_bits; i++){
	    string[i] = rhs.string[i];
	}
}

BinaryString& BinaryString::operator=(const BinaryString& rhs){
    BinaryString tmp(rhs);
    swap(*this, tmp);
    return *this;
}

//---------- MOVE SEMANTICS ----------------
BinaryString::BinaryString(BinaryString &&rhs)
    : BinaryString()
{
    swap(*this, rhs);
}

BinaryString& BinaryString::operator=(BinaryString &&rhs){
    swap(*this, rhs);
    return *this;
}


//----------- DESTRUCTOR ------------
BinaryString::~BinaryString(){
    delete[] string;
}

// ----------- MODIFIERS -------------
int& BinaryString::operator[](std::size_t idx){
    return string[idx];
}

BinaryString& BinaryString::operator++(){
    int index;
    for(index = n_bits-1; index >= 0; index--)
        if(string[index] == 0)
            break;
    if(index == -1)
        return *this;
    string[index] = 1;
    for(index += 1; index < n_bits; index++)
        if(string[index] == 1)
            string[index] = 0;
    return *this;
}

BinaryString BinaryString::operator++(int){
   BinaryString tmp(*this); // copy
   operator++(); // pre-increment
   return tmp;   // return old value
}

void BinaryString::reset(){
    for(int i = 0; i < n_bits; i++)
        string[i] = 0;
}

void BinaryString::generateRandomly(){
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < n_bits; ++i) {
        string[i] = dist(e2);
    }
}


// ------------ ACCESS METHODS ------------

int BinaryString::size(){
    return n_bits;
}

bool BinaryString::isIncrementable(){
    int index;
    if(n_bits == 0)
        return false;
    for(index = n_bits-1; index >= 0; index--)
        if(string[index] == 0)
            break;
    if(index == -1)
        return false;
    else
        return true;
}

