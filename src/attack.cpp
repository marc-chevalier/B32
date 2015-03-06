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
// greatest = greatest couple or not

bitset<BLOC_LENGTH> Attack::make_guess(pair<unsigned int, unsigned int> couple, unsigned int position, bool greatest)
{
    unsigned int nb_keys = static_cast<unsigned int>(pow(2.0,static_cast<double>(PIECE_LENGTH)));
    vector<unsigned int> frequencies(nb_keys,0);
    bitset<BLOC_LENGTH> A(couple.first);
    A = moveBitsets(A,position);
    cout << "A = " << A << endl;
    bitset<BLOC_LENGTH> PB(couple.second);
    PB = moveBitsets(PB,position+2);
    cout << "P(B) = " << PB << endl;
	for (unsigned int key = 0; key < nb_keys; ++key)
	{
        bitset<BLOC_LENGTH> K2(key);
        K2 = moveBitsets(K2,position);
        for (unsigned int i = 0; i < ciphertexts.size(); ++i)
        {
            bitset<BLOC_LENGTH> x1 = depasse(K2,ciphertexts[i]);
            if (produitScalaire(A,plaintexts[i]) == produitScalaire(PB,x1))
                frequencies[key]++;
        }
        cout << "Frequency of " << K2 << " : " << frequencies[key] << endl;
	}
	unsigned int good_guess = 0;
    for (unsigned int j = 0; j < nb_keys; ++j)
    {
        if (greatest) // look for the greatest value
        {
            if (frequencies[j] > frequencies[good_guess])
                good_guess = j;
        }
        else
        {
            if (frequencies[j] < frequencies[good_guess])
                good_guess = j;
        }
    }
	bitset<BLOC_LENGTH> guess(good_guess);
    return guess;
}

std::bitset<BLOC_LENGTH> moveBitsets(std::bitset<BLOC_LENGTH> Key, unsigned int position) // Works correctly
{
    int shift = BLOC_LENGTH - static_cast<int>(position) - PIECE_LENGTH;
    if (shift >= 0)
        return (Key<<static_cast<size_t>(shift))|(Key>>(BLOC_LENGTH-static_cast<size_t>(shift)));
    else
        return (Key>>static_cast<size_t>(-shift)|(Key<<(BLOC_LENGTH+static_cast<size_t>(shift))));
}


bool inline isOneActiveBox(unsigned int b) // hypothesis : 0 < b < 16
{
    return ((b < 4) || (b % 4 == 0));
}
