#pragma once
#include "std.h"
#include "chiffre.h"
#include "linearApproxMatrix.h"
#include<cstdint>
#include<vector>
#include<bitset>
#include<random>

/**
* Comme on s'y attend, ça répond à la question 5
**/

class TestQuestion5 : public Chiffre
{
public:
    TestQuestion5(std::vector<std::bitset<BLOC_LENGTH>> clefs, std::vector<std::bitset<BLOC_LENGTH>>SBox, unsigned int nb_plaintext = 100);
    ~TestQuestion5(){};
    void experiment(bool verbose);

private:
    std::bitset<BLOC_LENGTH> randomPlaintext(bool verbose);
    unsigned int nb_plaintext;
    LinearApproxMatrix mat;
};


