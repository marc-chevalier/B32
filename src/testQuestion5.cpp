#include "../include/testQuestion5.h"
#include "../include/linearApproxMatrix.h"
#include<cmath>
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

TestQuestion5::TestQuestion5(vector<bitset<BLOC_LENGTH>> clefs_, vector<bitset<BLOC_LENGTH>>SBox_, unsigned int nb_plaintext_):
Chiffre(clefs_, SBox_), nb_plaintext(nb_plaintext_), mat(SBox_)
{}

/**
* Réalise l'expérience demandée
**/

void TestQuestion5::experiment(bool verbose)
{
    unsigned int proba = 0;
    unsigned int a = mat.getMin(0).first;
    unsigned int b = mat.getMin(0).second; /// On prend juste un couple intéressant fournissant une proba de l'ordre de 0.125
    bitset<BLOC_LENGTH> A (a<<(BLOC_LENGTH-PIECE_LENGTH));
    bitset<BLOC_LENGTH> B (b<<(BLOC_LENGTH-PIECE_LENGTH));
    for(unsigned int step = 0; step < nb_plaintext; ++step)
    {
        bitset<BLOC_LENGTH> m = randomPlaintext(verbose);
        bitset<BLOC_LENGTH> PB = (B<<(BLOC_LENGTH-2))|(B>>2);
        if(produitScalaire(A, m) == produitScalaire(PB, passe(clefs[1], m^clefs[0])))
            proba++;
    }
    cout << "Probability found : " << static_cast<double>(proba)/static_cast<double>(nb_plaintext) << endl;
}

/**
* Génère un bloc aléatoire à partir de l'aléatoire de meilleure qualité : l'aléatoire matériel.
* A ne pas utiliser intensivement, il peut perdre en qualité ou être lent.
**/

bitset<BLOC_LENGTH> TestQuestion5::randomPlaintext(bool verbose)
{
    random_device random;
    bitset<BLOC_LENGTH> b;
    for(unsigned int i = 0; i < BLOC_LENGTH; i++)
        b[i]=random() % 2;
    if(verbose)
        cout << b << endl;
    return b;
}
