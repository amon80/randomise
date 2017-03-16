#ifndef BINARYSTRING_H
#define BINARYSTRING_H

#include <iostream>

class BinaryString
{
public:
    //rule of five
    //constructors
    BinaryString();
    BinaryString(int num_bits, int num_to_convert);
    BinaryString(int num_bits, bool random = false);
    //desturctor
    ~BinaryString();
    //copy semantics
    BinaryString(const BinaryString& rhs);
    BinaryString& operator=(const BinaryString& rhs);
    //move semantics
    BinaryString(BinaryString&& rhs);
    BinaryString& operator=(BinaryString&& rhs);
    //modifiers
    int& operator[](std::size_t idx);
    BinaryString& operator++();
    BinaryString operator++(int);
    //access functions
    int size();
    
private:
    friend std::ostream& operator<<(std::ostream &os, const BinaryString& p);
    friend void swap(BinaryString& first, BinaryString& second);
    friend bool operator<(const BinaryString& first, const BinaryString& second);
    friend bool operator==(const BinaryString& first, const BinaryString& second);
    friend bool operator>(const BinaryString& first, const BinaryString& second);
    int n_bits;
    int * string;
};

inline bool operator!=(const BinaryString& first, const BinaryString& second){return !(first == second);}

#endif // BINARYSTRING_H
