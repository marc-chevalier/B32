#include "../include/parseur.h"
#include<fstream>
#include<iostream>

using namespace std;

vector<bitset<BLOC_LENGTH>> Parseur::parseClefs(string clefs_filename)
{
    vector<bitset<BLOC_LENGTH>> clefs(0);
    ifstream clefs_file(clefs_filename, ifstream::in);
    size_t nbr_clefs;
    clefs_file>>nbr_clefs;
    clefs = vector<bitset<BLOC_LENGTH>>(nbr_clefs);
    for(size_t i=0;i<nbr_clefs;++i)
    {
        string w;
        clefs_file>>w;
        clefs[i]=bitset<BLOC_LENGTH>(w);
    }
    clefs_file.close();
    return clefs;
}

vector<bitset<BLOC_LENGTH>> Parseur::parseText(string text_filename)
{
    vector<bitset<BLOC_LENGTH>> text(1);
    ifstream text_file(text_filename, ifstream::in);
    char c;
    size_t i=0;
    int j=-1;
    while(text_file.get(c))
    {
        if(j==BLOC_LENGTH-1)
        {
            i++;
            text.push_back(bitset<BLOC_LENGTH>(0));
        }
        j++;
        j%=BLOC_LENGTH;
        text[i][static_cast<size_t>(BLOC_LENGTH-j-1)] = c-'0';

    }
    text_file.close();

    return text;
}

vector<bitset<BLOC_LENGTH>> Parseur::parseSBox(string sbox_filename)
{
    vector<bitset<BLOC_LENGTH>> SBox(1<<PIECE_LENGTH);
    ifstream sbox_file(sbox_filename, ifstream::in);
    for(size_t k=0;k<1<<PIECE_LENGTH;++k)
    {
        long long unsigned int w;
        sbox_file>>w;
        SBox[k]=bitset<BLOC_LENGTH>(w);
    }
    sbox_file.close();
    return SBox;
}
