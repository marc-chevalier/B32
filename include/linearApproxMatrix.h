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
    void build_farthest_couples();
    void print_farthest_couples();
    unsigned int get_min(unsigned int index) __attribute__((pure));
    unsigned int get_max(unsigned int index) __attribute__((pure));
private:
    std::vector<std::vector<int>> matrix;
    std::vector<unsigned int> minima;
    std::vector<unsigned int> maxima;
};

bool produitScalaire(std::bitset<BLOC_LENGTH> a, std::bitset<BLOC_LENGTH> b)  __attribute__((pure));
std::ostream& operator<<(std::ostream& flux, linearApproxMatrix approx);

