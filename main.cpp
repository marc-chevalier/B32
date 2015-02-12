#include <iostream>
#include <cstdlib>
#include <vector>
#include "include/chiffre.h"
#include "include/parseur.h"
#include "include/std.h"
#include "include/argumentsParseur.h"

using namespace std;

int main(int argc, char* argv[])
{
    ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxes :"<<endl;
        cout<<"./B32 -c keys sbox plaintext"<<endl;

        cout<<"-c               Chiffrer"<<endl;
        cout<<"-h               Vous y êtes"<<endl;
        cout<<"--help           Vous y êtes"<<endl<<endl;
        return(EXIT_SUCCESS);
    }
    if(arguments.getOption("c"))
    {
        if(arguments.nbArguments()!=3)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -c keys sbox plaintext"<<endl;
        }
        Chiffre test(Parseur::parseClefs(arguments.getArgument(0)), Parseur::parseSBox(arguments.getArgument(1)));
        vector<bitset<BLOC_LENGTH>> ciphertext=test.chiffrer(Parseur::parseText(arguments.getArgument(2)));
        for(bitset<BLOC_LENGTH> bloc : ciphertext)
            cout<<bloc;
    }

    if(argc != 3)
    {
        cerr<<"Utilisation : ./B32 keys sbox plaintext"<<endl;
        return EXIT_FAILURE;
    }

    return 0;
}
