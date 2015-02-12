#include <iostream>
#include <cstdlib>
#include <vector>
#include "include/chiffre.h"
#include "include/parseur.h"
#include "include/std.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<bitset<BLOC_LENGTH>> clefs(3);
    clefs[0]=bitset<BLOC_LENGTH>(string("10000000000000000000000000000001"));
    clefs[1]=bitset<BLOC_LENGTH>(string("11111111111111111111111111111111"));
    clefs[2]=bitset<BLOC_LENGTH>(string("01111111111111111111111111111110"));
    bitset<BLOC_LENGTH> SBoc_liste[]={7,3,6,1,13,9,10,11,2,12,0,4,5,15,8,14};
    vector<bitset<BLOC_LENGTH>> SBox(SBoc_liste, SBoc_liste+16);
    Chiffre test(clefs, SBox);
    vector<bitset<BLOC_LENGTH>> plaintext(1,0);
    bitset<BLOC_LENGTH> result(string("00111001011001100110011001100110"));
    cout<<(test.chiffrer(plaintext)[0]==result)<<endl;


    if(argc != 3)
    {
        cerr<<"Utilisation : B32 keys plaintext"<<endl;
        return EXIT_FAILURE;
    }

    Parseur parseur(argv[1], argv[2]);

    return 0;
}
