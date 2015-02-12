#include <iostream>
#include <cstdlib>
#include <vector>
#include "include/chiffre.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<uint32_t> clefs(3);
    clefs[0]=128+1;
    clefs[1]=255;
    clefs[2]=128-2;
    vector<uint32_t> SBox(16);
    SBox[0]=7;
    SBox[1]=3;
    SBox[2]=6;
    SBox[3]=1;
    SBox[4]=13;
    SBox[5]=9;
    SBox[6]=10;
    SBox[7]=11;
    SBox[8]=2;
    SBox[9]=12;
    SBox[10]=0;
    SBox[11]=4;
    SBox[12]=5;
    SBox[13]=15;
    SBox[14]=8;
    SBox[15]=14;
    Chiffre test(clefs, SBox);
    vector<uint32_t> plaintext(1,0);
    cout<<test.chiffrer(plaintext)[0]<<endl;


    if(argc != 3)
    {
        cerr<<"Utilisation : B32 keys plaintext"<<endl;
        return EXIT_FAILURE;
    }
    return 0;
}
