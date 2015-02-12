#include "../include/chiffre.h"
#include<cmath>
#include<iostream>

using namespace std;

vector<bitset<BLOC_LENGTH>> Chiffre::chiffrer(vector<bitset<BLOC_LENGTH>> plaintext)
{
    vector<bitset<BLOC_LENGTH>> ciphertext(plaintext.size());

    for(unsigned int i=0;i<plaintext.size();++i)
        ciphertext[i]=chiffrerBloc(plaintext[i]);

    return ciphertext;
}

bitset<BLOC_LENGTH> Chiffre::chiffrerBloc(bitset<BLOC_LENGTH> plaintext)
{
    plaintext = plaintext^clefs[0];
    for(unsigned int i=1;i<clefs.size();++i)
        plaintext=passe(clefs[i], plaintext);

    return plaintext;
}

bitset<BLOC_LENGTH> Chiffre::passe(bitset<BLOC_LENGTH> clef, bitset<BLOC_LENGTH> input)
{
    int taillePiece = static_cast<int>(log2(SBox.size()));
    int nbPiece = (input.size())/taillePiece;
    bitset<BLOC_LENGTH> output=0;

    for(int i=0;i<nbPiece;++i)
    {
        bitset<BLOC_LENGTH> masque = creerMasque(taillePiece*i, taillePiece*(i+1)-1);
        bitset<BLOC_LENGTH> piece = input & masque;
        piece >>= taillePiece*i;
        piece = SBox[piece.to_ulong()];
        piece <<= taillePiece*i;
        output |= piece;
    }

    return ((output<<BLOC_LENGTH-2)|(output>>2))^clef;
}

bitset<BLOC_LENGTH> Chiffre::creerMasque(int debut, int fin)
{
    bitset<BLOC_LENGTH> sortie=0;
    for(int i=debut; i<=fin; ++i)
        sortie |= 1<<i;

    return sortie;
}
