#include "../include/chiffre.h"
#include<cmath>
#include<iostream>

using namespace std;

vector<uint32_t> Chiffre::chiffrer(vector<uint32_t> plaintext)
{
    vector<uint32_t> ciphertext(plaintext.size());

    for(unsigned int i=0;i<plaintext.size();++i)
        ciphertext[i]=chiffrerBloc(plaintext[i]);

    return ciphertext;
}

uint32_t Chiffre::chiffrerBloc(uint32_t plaintext)
{
    plaintext = plaintext^clefs[0];
    for(unsigned int i=1;i<clefs.size();++i)
        plaintext=passe(clefs[i], plaintext);

    return plaintext;
}

uint32_t Chiffre::passe(uint32_t clef, uint32_t input)
{
    int taillePiece = static_cast<int>(log2(SBox.size()));
    int nbPiece = (8*sizeof(uint32_t))/taillePiece;
    cout<<taillePiece<<endl;
    cout<<nbPiece<<endl;
    uint32_t output=0;

    for(int i=0;i<nbPiece;++i)
    {
        uint32_t masque = creerMasque(taillePiece*i, taillePiece*(i+1)-1);
        uint32_t piece = input & masque;
        piece >>= taillePiece*i;
        piece = SBox[piece];
        piece <<= taillePiece*i;
        output |= piece;
    }

    return ((output<<30)|(output>>2))^clef;
}

uint32_t Chiffre::creerMasque(int debut, int fin)
{
    uint32_t sortie=0;
    for(int i=debut; i<=fin; ++i)
        sortie |= 1<<i;

    return sortie;
}
