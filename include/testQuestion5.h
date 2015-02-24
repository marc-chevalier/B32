#pragma once
#include "std.h"
#include "chiffre.h"
#include "linearApproxMatrix.h"
#include<cstdint>
#include<vector>
#include<bitset>

class TestQuestion5 : public Chiffre
{
public:
    TestQuestion5(std::vector<std::bitset<BLOC_LENGTH>> clefs_, std::vector<std::bitset<BLOC_LENGTH>>SBox_, unsigned int nb_plaintext_ = 100);
    ~TestQuestion5(){};
    void experiment();
private:
    unsigned int nb_plaintext;
    linearApproxMatrix mat;
};

std::bitset<BLOC_LENGTH> randomPlaintext();
