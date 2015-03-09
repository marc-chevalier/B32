#pragma once
#include "std.h"
#include "linearApproxMatrix.h"
#include "chiffre.h"
#include <vector>

/**
* Classe qui fait l'attaque du chiffre.
**/

class Attack : public LinearApproxMatrix, public Chiffre
{
public:
    Attack(std::vector<std::bitset<BLOC_LENGTH>> plaintexts, std::vector<std::bitset<BLOC_LENGTH>> ciphertexts, std::vector<std::bitset<BLOC_LENGTH>>SBox);
    ~Attack() {};
    std::bitset<BLOC_LENGTH> buildSecretKey(std::bitset<BLOC_LENGTH> K0, std::bitset<BLOC_LENGTH> K1, std::bitset<BLOC_LENGTH> K2);
    bool inline checkKeys(std::bitset<BLOC_LENGTH> K0, std::bitset<BLOC_LENGTH> K1, std::bitset<BLOC_LENGTH> K2, unsigned int position);
    void depasseCiphertexts(std::bitset<BLOC_LENGTH> K);
    void findAllKeys(bool active_box);
    std::bitset<BLOC_LENGTH> findK2(bool active_box);
    std::pair<std::bitset<BLOC_LENGTH>, std::bitset<BLOC_LENGTH>> findSubK0K1(std::bitset<BLOC_LENGTH> K2, unsigned int position);
    unsigned int makeGuess(bool active_box, unsigned int position);

private:
    std::vector<std::bitset<BLOC_LENGTH>> plaintexts;
    std::vector<std::bitset<BLOC_LENGTH>> ciphertexts;
    std::vector<std::pair<unsigned int, unsigned int>> one_active_pairs;
    std::vector<std::pair<unsigned int, unsigned int>> two_active_pairs;
};

bool isOneActiveBox(unsigned int b) __attribute__((pure));
std::bitset<BLOC_LENGTH> moveBitsets(std::bitset<BLOC_LENGTH> Key, unsigned int position) __attribute__((pure));

