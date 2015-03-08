#pragma once
#include "std.h"
#include<string>
#include<bitset>
#include<vector>

/**
* Lit des fichiers de texte de taille arbitaire et les sépare en blocs.
* Lit les fichiers contenant les clefs et la sbox
**/

class Parseur
{
public:
    Parseur(){};
    ~Parseur(){};
    static std::vector<std::bitset<BLOC_LENGTH>> parseClefs(std::string clefs_filename);
    static std::vector<std::bitset<BLOC_LENGTH>> parseSBox(std::string plaintext_filename);
    static std::vector<std::bitset<BLOC_LENGTH>> parseText(std::string sbox_filename);

private:
};
