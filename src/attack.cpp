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

unsigned int Attack::make_guess(bool active_box, unsigned int position, bool verbose)
{
    unsigned int nb_keys = static_cast<unsigned int>(pow(2.0,static_cast<double>(PIECE_LENGTH)));
    vector<int> biais(nb_keys,0);
    vector<pair<unsigned int, unsigned int>> couples;
    if (active_box) // one active box
        couples = one_active_pairs;
    else
        couples = two_active_pairs;
    for (unsigned int k = 0; k < couples.size(); ++k)
    {

        bitset<BLOC_LENGTH> A(couples[k].first);
        A = moveBitsets(A,PIECE_LENGTH*position);
        if(verbose)
            cout << "A = " << A << endl; // OK
        bitset<BLOC_LENGTH> PB(couples[k].second);
        PB = moveBitsets(PB,PIECE_LENGTH*position+2);
        if(verbose)
            cout << "P(B) = " << PB << endl; // OK
        for (unsigned int key = 0; key < nb_keys; ++key)
        {
            int frequency = 0;
            bitset<BLOC_LENGTH> K2(key);
            K2 = moveBitsets(K2,PIECE_LENGTH*position+2); // OK
            for (unsigned int i = 0; i < ciphertexts.size(); ++i)
            {
                bitset<BLOC_LENGTH> x1 = depasse(K2,ciphertexts[i]);
                if (produitScalaire(A,plaintexts[i]) == produitScalaire(PB,x1))
                    frequency++;
            }
            biais[key] += abs(frequency - static_cast<int>(ciphertexts.size())/2);
        }
    }

	// Find the good guess = greatest biais
	unsigned int good_guess = 0;
    for (unsigned int key = 0; key < nb_keys; ++key)
        if (biais[key] > biais[good_guess])
            good_guess = key;

	return good_guess;
}

bitset<BLOC_LENGTH> Attack::find_K2(bool active_box, bool verbose)
{
    bitset<BLOC_LENGTH> result(0);
    for (unsigned int position = 0; position < BLOC_LENGTH/PIECE_LENGTH; ++position)
    {
        unsigned int guess = make_guess(active_box, position, verbose);
        bitset<BLOC_LENGTH> subkey(guess);
        if(verbose)
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
