#pragma once
#include "std.h"
#include<cstdint>
#include<vector>
#include<bitset>

class Chiffre
{
public:
    Chiffre(std::vector<std::bitset<BLOC_LENGTH>> clefs_, std::vector<std::bitset<BLOC_LENGTH>>SBox_) : clefs(clefs_), SBox(SBox_) {};
    ~Chiffre(){};
    std::vector<std::bitset<BLOC_LENGTH>> chiffrer(std::vector<std::bitset<BLOC_LENGTH>> plaintext);

private:
    std::bitset<BLOC_LENGTH> chiffrerBloc(std::bitset<BLOC_LENGTH> plaintext);
    std::bitset<BLOC_LENGTH> passe(std::bitset<BLOC_LENGTH> clef, std::bitset<BLOC_LENGTH> input);
    std::bitset<BLOC_LENGTH> creerMasque(int debut, int fin);
    std::vector<std::bitset<BLOC_LENGTH>> clefs;
    std::vector<std::bitset<32>> SBox;
};

