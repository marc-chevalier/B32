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

unsigned int Attack::make_guess(pair<unsigned int, unsigned int> couple, unsigned int position)
{
    unsigned int nb_keys = static_cast<unsigned int>(pow(2.0,static_cast<double>(PIECE_LENGTH)));
    vector<int> frequencies(nb_keys,0);
    bitset<BLOC_LENGTH> A(couple.first);
    A = moveBitsets(A,PIECE_LENGTH*position);
    cout << "A = " << A << endl; // OK
    bitset<BLOC_LENGTH> PB(couple.second);
    PB = moveBitsets(PB,PIECE_LENGTH*position+2);
    cout << "P(B) = " << PB << endl; // OK
	for (unsigned int key = 0; key < nb_keys; ++key)
	{
        bitset<BLOC_LENGTH> K2(key);
        K2 = moveBitsets(K2,PIECE_LENGTH*position+2); // OK
        for (unsigned int i = 0; i < ciphertexts.size(); ++i)
        {
            if (key == 0)
                cout << plaintexts[i] << endl;
            bitset<BLOC_LENGTH> x1 = depasse(K2,ciphertexts[i]);
            if (produitScalaire(A,plaintexts[i]) == produitScalaire(PB,x1))
                frequencies[key]++;
        }
        cout << "Frequency of " << K2 << " : " << frequencies[key] << endl;
	}
	// Compute biais
	for (unsigned int j = 0; j < nb_keys; ++j)
        frequencies[j] = abs(frequencies[j] - static_cast<int>(ciphertexts.size())/2);

	// Find the good guess = greatest biais
	unsigned int good_guess = 0;
    for (unsigned int j = 0; j < nb_keys; ++j)
        if (frequencies[j] > frequencies[good_guess])
            good_guess = j;
	return good_guess;
}

bitset<BLOC_LENGTH> Attack::find_K2(pair<unsigned int, unsigned int> couple)
{
    bitset<BLOC_LENGTH> result(0);
    for (unsigned int position = 0; position < BLOC_LENGTH/PIECE_LENGTH; ++position)
    {
        unsigned int guess = make_guess(couple,position);
        bitset<BLOC_LENGTH> subkey(guess);
        cout << guess << endl;
        subkey = moveBitsets(subkey,PIECE_LENGTH*position + 2);
        result |= subkey;
    }
    return result;
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
