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

void TestQuestion5::experiment(bool verbose)
{
    unsigned int proba = 0;
    unsigned int a = mat.get_min(0).first;
    unsigned int b = mat.get_min(0).first; // Example
    bitset<BLOC_LENGTH> A (a<<(BLOC_LENGTH-4));
    bitset<BLOC_LENGTH> B (b<<(BLOC_LENGTH-4));
    for (unsigned int step = 0; step < nb_plaintext; ++step)
    {
        bitset<BLOC_LENGTH> m = randomPlaintext(verbose);
        bitset<BLOC_LENGTH> x;
        x = m^clefs[0]; // we get x_0
        x = passe(x,clefs[1]); // we get x_1
        bitset<BLOC_LENGTH> PB = (B<<(BLOC_LENGTH-2))|(B>>2);
        if (produitScalaire(A,m) == produitScalaire(PB,x))
            proba++;
    }
    cout << "Probability found : " << static_cast<double>(proba)/static_cast<double>(nb_plaintext) << endl;
}

bitset<BLOC_LENGTH> TestQuestion5::randomPlaintext(bool verbose)
{
    random_device random;
    bitset<BLOC_LENGTH> b;
    for (unsigned int i = 0; i < BLOC_LENGTH; i++)
        b[i]=random() % 2;
    if(verbose)
        cout << b << endl;
    return b;
}
