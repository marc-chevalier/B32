#pragma once
#include<vector>
#include<bitset>
#include<iostream>
#include "std.h"

/**
* Construit la matrice L d'approximation linéaire de la SBox et propriétés simples
**/

class LinearApproxMatrix
{
public:
    LinearApproxMatrix(std::vector<std::bitset<BLOC_LENGTH>>SBox);
    virtual ~LinearApproxMatrix(){};
    void buildFarthestCouples();
    std::pair<unsigned int, unsigned int> getMin(unsigned int index) __attribute__((pure));
    std::pair<unsigned int, unsigned int> getMax(unsigned int index) __attribute__((pure));
    void print(std::ostream& flux);
    void printFarthestCouples();
protected:
    std::vector<std::vector<int>> matrix;
    std::vector<std::pair<unsigned int, unsigned int>> minima;
    std::vector<std::pair<unsigned int, unsigned int>> maxima;
};

bool produitScalaire(std::bitset<BLOC_LENGTH> a, std::bitset<BLOC_LENGTH> b)  __attribute__((pure));
std::ostream& operator<<(std::ostream& flux, LinearApproxMatrix approx);

