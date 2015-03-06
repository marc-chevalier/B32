#include "../include/attack.h"
#include <vector>
#include <cmath> // pow

using namespace std;

Attack::Attack(vector<bitset<BLOC_LENGTH>> plaintexts_, vector<bitset<BLOC_LENGTH>> ciphertexts_, vector<bitset<BLOC_LENGTH>>SBox_)
: linearApproxMatrix(SBox_),  Chiffre(SBox_), plaintexts(plaintexts_), ciphertexts(ciphertexts_),
  one_active_pairs(vector<pair<unsigned int, unsigned int>>()), two_active_pairs(vector<pair<unsigned int, unsigned int>>())
{
    for (auto couple : minima)
    {
        if (isOneActiveBox(couple.second))
            one_active_pairs.push_back(couple);
        else
            two_active_pairs.push_back(couple);
    }

    for (auto couple : maxima)
    {
        if (isOneActiveBox(couple.second))
            one_active_pairs.push_back(couple);
        else
            two_active_pairs.push_back(couple);
    }
    for (unsigned int i=0;i<SBox_.size();++i)
        invSBox[SBox_[i].to_ulong()]=std::bitset<BLOC_LENGTH>(i);
}

// Attack in the general case (no notion of active boxes)
// Just try to guess the 4 bits of the key (2,3,4,5 if position = 0, with the example of the report)

bitset<BLOC_LENGTH> Attack::make_guess(pair<unsigned int, unsigned int> couple, unsigned int position)
{
    unsigned int nb_keys = static_cast<unsigned int>(pow(2.0,static_cast<double>(PIECE_LENGTH)));
    vector<unsigned int> frequencies(nb_keys,0);
    bitset<BLOC_LENGTH> A(couple.first);
    A = A<<(BLOC_LENGTH-PIECE_LENGTH*position);
    bitset<BLOC_LENGTH> PB(couple.second);
    PB = PB<<(BLOC_LENGTH-PIECE_LENGTH*position);
    PB = (PB<<BLOC_LENGTH-2)|(PB>>2);
	for (unsigned int key = 0; key < nb_keys; ++key)
	{
        bitset<BLOC_LENGTH> K2(key);
        K2 = moveKey(K2,position);
        // cout << K2 << endl; // Check of moveKey
        for (unsigned int i = 0; i < ciphertexts.size(); ++i)
        {
            bitset<BLOC_LENGTH> x1 = depasse(K2,ciphertexts[i]);
            if (produitScalaire(A,plaintexts[i]) == produitScalaire(PB,x1))
                frequencies[key]++;
        }
        cout << "Frequency of " << key << " : " << frequencies[key] << endl;
	}
	bitset<BLOC_LENGTH> guess(0);
    return guess;
}

std::bitset<BLOC_LENGTH> moveKey(std::bitset<BLOC_LENGTH> Key, unsigned int position) // Works correctly
{
    unsigned int shift = BLOC_LENGTH - PIECE_LENGTH *(position + 1);
    return (Key<<shift);
}
bool inline isOneActiveBox(unsigned int b) // hypothesis : 0 < b < 16
{
    return ((b < 4) || (b % 4 == 0));
}
