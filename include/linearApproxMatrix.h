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
    void print(std::ostream& flux);
	void farthest_couples();

private:
    std::vector< std::vector<int> > matrix;
};

bool prod(std::bitset<BLOC_LENGTH> a, std::bitset<BLOC_LENGTH> b)  __attribute__((pure));
std::ostream& operator<<(std::ostream& flux, linearApproxMatrix approx);
