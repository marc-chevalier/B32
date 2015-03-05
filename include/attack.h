#pragma once
#include "std.h"
#include "linearApproxMatrix.h"
#include "chiffre.h"
#include <vector>


class Attack : public linearApproxMatrix {
public:
    Attack(std::vector<std::bitset<BLOC_LENGTH>> plaintexts_, std::vector<std::bitset<BLOC_LENGTH>> ciphertexts_, std::vector<std::bitset<BLOC_LENGTH>>SBox_);
    ~Attack() {};

private:
    std::vector<std::bitset<BLOC_LENGTH>> plaintexts;
    std::vector<std::bitset<BLOC_LENGTH>> ciphertexts;
    std::vector<std::bitset<BLOC_LENGTH>> SBox;
    std::vector<std::pair<unsigned int, unsigned int>> one_active_pairs;
    std::vector<std::pair<unsigned int, unsigned int>> two_active_pairs;

};

bool isOneActiveBox(unsigned int b) __attribute__((pure)); // one or two active boxes

