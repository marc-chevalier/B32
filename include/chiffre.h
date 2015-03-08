#pragma once
#include "std.h"
#include<cstdint>
#include<vector>
#include<bitset>

/**
* Implémentation du chiffre
**/

class Chiffre
{
public:
    Chiffre(std::vector<std::bitset<BLOC_LENGTH>> clefs_, std::vector<std::bitset<BLOC_LENGTH>>SBox_);
    Chiffre(std::vector<std::bitset<BLOC_LENGTH>> SBox_);
    virtual ~Chiffre(){};
    std::vector<std::bitset<BLOC_LENGTH>> chiffrer(std::vector<std::bitset<BLOC_LENGTH>> plaintext);
    std::vector<std::bitset<BLOC_LENGTH>> dechiffrer(std::vector<std::bitset<BLOC_LENGTH>> plaintext);

protected:
    std::bitset<BLOC_LENGTH> passe(std::bitset<BLOC_LENGTH> clef, std::bitset<BLOC_LENGTH> input);
    std::bitset<BLOC_LENGTH> creerMasque(size_t debut, size_t fin);
    std::bitset<BLOC_LENGTH> depasse(std::bitset<BLOC_LENGTH> clef, std::bitset<BLOC_LENGTH> input);
    std::vector<std::bitset<BLOC_LENGTH>> clefs;
    std::vector<std::bitset<BLOC_LENGTH>> SBox;
    std::vector<std::bitset<BLOC_LENGTH>> invSBox;

private:
    std::bitset<BLOC_LENGTH> dechiffrerBloc(std::bitset<BLOC_LENGTH> plaintext);
    std::bitset<BLOC_LENGTH> chiffrerBloc(std::bitset<BLOC_LENGTH> plaintext);

};

