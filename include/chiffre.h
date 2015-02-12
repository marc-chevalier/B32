#pragma once
#include<cstdint>
#include<vector>

class Chiffre
{
public:
    Chiffre(std::vector<uint32_t> clefs_, std::vector<uint32_t>SBox_) : clefs(clefs_), SBox(SBox_) {};
    ~Chiffre(){};
    std::vector<uint32_t> chiffrer(std::vector<uint32_t> plaintext);

private:
    uint32_t chiffrerBloc(uint32_t plaintext);
    uint32_t passe(uint32_t clef, uint32_t input);
    uint32_t creerMasque(int debut, int fin);
    std::vector<uint32_t> clefs;
    std::vector<uint32_t> SBox;
};

