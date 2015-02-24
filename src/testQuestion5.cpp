#include "../include/testQuestion5.h"
#include "../include/linearApproxMatrix.h" // prod
#include<cmath>
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

TestQuestion5::TestQuestion5(vector<bitset<BLOC_LENGTH>> clefs_, vector<bitset<BLOC_LENGTH>>SBox_, unsigned int nb_plaintext_):
Chiffre(clefs_, SBox_), nb_plaintext(nb_plaintext_), mat(SBox_)
{
    srand(static_cast<unsigned int>(time(NULL)));
}

void TestQuestion5::experiment()
{
    unsigned int proba = 0;
    unsigned int a = mat.get_min(0);
    unsigned int b = mat.get_min(1); // Example
    bitset<BLOC_LENGTH> A (a<<(BLOC_LENGTH-4));
    bitset<BLOC_LENGTH> B (b<<(BLOC_LENGTH-4));
    for (unsigned int step = 0; step < nb_plaintext; ++step)
    {
        bitset<BLOC_LENGTH> m = randomPlaintext();
        bitset<BLOC_LENGTH> x;
        x = m^clefs[0]; // we get x_0
        x = passe(x,clefs[1]); // we get x_1
        bitset<BLOC_LENGTH> PB = B;
        PB = (PB<<(BLOC_LENGTH-2))|(PB>>2);
        if (prod(A,m) == prod(PB,x))
            proba++;
    }
    cout << "Probability found : " << static_cast<double>(proba)/static_cast<double>(nb_plaintext) << endl;
}

bitset<BLOC_LENGTH> randomPlaintext()
{
    unsigned long n = 0;
    for (unsigned int i = 0; i < BLOC_LENGTH; i++)
    {
        n *= 2;
        n += static_cast<unsigned long>(rand() % 2);
    }
    bitset<BLOC_LENGTH> b(n);
    cout << b << endl;
    return b;
}
