#pragma once
#include "std.h"
#include "linearApproxMatrix.h"
#include "chiffre.h"
#include <vector>


class Attack : public linearApproxMatrix, public Chiffre {
public:
    Attack(std::vector<std::bitset<BLOC_LENGTH>> plaintexts_, std::vector<std::bitset<BLOC_LENGTH>> ciphertexts_, std::vector<std::bitset<BLOC_LENGTH>>SBox_);
    ~Attack() {};
    unsigned int make_guess(bool active_box, unsigned int position);
    void depasse_ciphertexts(std::bitset<BLOC_LENGTH> K);
    std::bitset<BLOC_LENGTH> find_K2(bool active_box);
    bool inline check_keys(std::bitset<BLOC_LENGTH> K0, std::bitset<BLOC_LENGTH> K1, std::bitset<BLOC_LENGTH> K2, int position);
    std::pair<std::bitset<BLOC_LENGTH>, std::bitset<BLOC_LENGTH>> find_sub_K0_K1(std::bitset<BLOC_LENGTH> K2, int position);
    std::bitset<BLOC_LENGTH> build_secret_key(std::bitset<BLOC_LENGTH> K0, std::bitset<BLOC_LENGTH> K1, std::bitset<BLOC_LENGTH> K2);
    void find_all_keys(bool active_box);

private:
    std::vector<std::bitset<BLOC_LENGTH>> plaintexts;
    std::vector<std::bitset<BLOC_LENGTH>> ciphertexts;
    std::vector<std::pair<unsigned int, unsigned int>> one_active_pairs;
    std::vector<std::pair<unsigned int, unsigned int>> two_active_pairs;

};

bool isOneActiveBox(unsigned int b) __attribute__((pure)); // one or two active boxes
std::bitset<BLOC_LENGTH> moveBitsets(std::bitset<BLOC_LENGTH> Key, unsigned int position) __attribute__((pure));

