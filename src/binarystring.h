#ifndef BINARYSTRING_H
#define BINARYSTRING_H

#include <iostream>

class StatisticalMap3D;

class BinaryString
{
public:
    //rule of five
    //constructors
    BinaryString();
    BinaryString(int num_bits, int num_to_convert);
    BinaryString(int num_bits, bool random = false);
    BinaryString(StatisticalMap3D& map, bool (*confront)(const float, const float), const float value);
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
    void reset();
    void generateRandomly();
    //access functions
    int size();
    bool isIncrementable();
    
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

bool moreThan(float a, float b);
bool lessThan(float a, float b);


#endif // BINARYSTRING_H
