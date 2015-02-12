#pragma once
#include "std.h"
#include<string>
#include<bitset>
#include<vector>

class Parseur
{
public:
    Parseur(std::string clefs_file, std::string plaintext_file);
    ~Parseur(){};

private:
    std::vector<std::bitset<BLOC_LENGTH>> clefs;
    std::vector<std::bitset<BLOC_LENGTH>> plaintext;
};
