#include "../include/parseur.h"
#include<fstream>
#include<iostream>

using namespace std;

std::vector<std::bitset<BLOC_LENGTH>> Parseur::parseClefs(std::string clefs_filename)
{
    std::vector<std::bitset<BLOC_LENGTH>> clefs(0);
    ifstream clefs_file(clefs_filename, ifstream::in);
    int nbr_clefs;
    clefs_file>>nbr_clefs;
    clefs = vector<bitset<BLOC_LENGTH>>(nbr_clefs);
    for(int i=0;i<nbr_clefs;++i)
    {
        string w;
        clefs_file>>w;
        clefs[i]=bitset<BLOC_LENGTH>(w);
    }
    clefs_file.close();
    return clefs;
}

std::vector<std::bitset<BLOC_LENGTH>> Parseur::parseText(std::string text_filename)
{
    vector<bitset<BLOC_LENGTH>> text(1);
    ifstream text_file(text_filename, ifstream::in);
    char c;
    int i=0;
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
        text[i][BLOC_LENGTH-j-1] = c-'0';

    }
    text_file.close();

    return text;
}

std::vector<std::bitset<BLOC_LENGTH>> Parseur::parseSBox(std::string sbox_filename)
{
    vector<bitset<BLOC_LENGTH>> SBox(1<<PIECE_LENGTH);
    ifstream sbox_file(sbox_filename, ifstream::in);
    for(int k=0;k<1<<PIECE_LENGTH;++k)
    {
        int w;
        sbox_file>>w;
        SBox[k]=bitset<BLOC_LENGTH>(w);
    }
    sbox_file.close();
    return SBox;
}
