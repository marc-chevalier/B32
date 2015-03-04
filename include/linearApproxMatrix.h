#pragma once
#include<vector>
#include<bitset>
#include<iostream>
#include "std.h"

class linearApproxMatrix
{
public:
    linearApproxMatrix(std::vector<std::bitset<BLOC_LENGTH>>SBox);
    virtual ~linearApproxMatrix(){};
    void print(std::ostream& flux);
    void build_farthest_couples();
    void print_farthest_couples();
    std::pair<unsigned int, unsigned int> get_min(unsigned int index) __attribute__((pure));
    std::pair<unsigned int, unsigned int> get_max(unsigned int index) __attribute__((pure));
protected:
    std::vector<std::vector<int>> matrix;
    std::vector<std::pair<unsigned int, unsigned int>> minima;
    std::vector<std::pair<unsigned int, unsigned int>> maxima;
};

bool produitScalaire(std::bitset<BLOC_LENGTH> a, std::bitset<BLOC_LENGTH> b)  __attribute__((pure));
std::ostream& operator<<(std::ostream& flux, linearApproxMatrix approx);

