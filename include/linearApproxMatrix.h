#pragma once
#include<vector>
#include<bitset>
#include<iostream>
#include "std.h"

class linearApproxMatrix
{
public:
    linearApproxMatrix(std::vector<std::bitset<BLOC_LENGTH>>SBox);
    ~linearApproxMatrix(){};
    void print(std::ofstream& flux) const;

private:
    std::vector< std::vector<int> > matrix;
};

bool prod(std::bitset<BLOC_LENGTH> a, std::bitset<BLOC_LENGTH> b);
std::ofstream& operator<<(std::ofstream& flux, linearApproxMatrix approx);
