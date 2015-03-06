#pragma once
#include "std.h"
#include "linearApproxMatrix.h"
#include "chiffre.h"
#include <vector>


class Attack : public linearApproxMatrix, public Chiffre {
public:
    Attack(std::vector<std::bitset<BLOC_LENGTH>> plaintexts_, std::vector<std::bitset<BLOC_LENGTH>> ciphertexts_, std::vector<std::bitset<BLOC_LENGTH>>SBox_);
    ~Attack() {};
    std::bitset<BLOC_LENGTH> make_guess(std::pair<unsigned int, unsigned int> couple, unsigned int position, bool greatest);

private:
    std::vector<std::bitset<BLOC_LENGTH>> plaintexts;
    std::vector<std::bitset<BLOC_LENGTH>> ciphertexts;
    std::vector<std::pair<unsigned int, unsigned int>> one_active_pairs;
    std::vector<std::pair<unsigned int, unsigned int>> two_active_pairs;

};

bool isOneActiveBox(unsigned int b) __attribute__((pure)); // one or two active boxes
std::bitset<BLOC_LENGTH> moveBitsets(std::bitset<BLOC_LENGTH> Key, unsigned int position) __attribute__((pure));

