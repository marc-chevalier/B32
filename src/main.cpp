#include <iostream>
#include <cstdlib>
#include <vector>
#include "../include/chiffre.h"
#include "../include/parseur.h"
#include "../include/std.h"
#include "../include/argumentsParseur.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxes :"<<endl;
        cout<<"    ./B32 -c keys sbox plaintext"<<endl;
        cout<<"    ./B32 -d keys sbox ciphertext"<<endl<<endl;

        cout<<"-c               Chiffrer"<<endl;
        cout<<"-d               Déchiffrer"<<endl;
        cout<<"-h               Vous y êtes"<<endl;
        cout<<"--help           Vous y êtes"<<endl<<endl;
        return EXIT_SUCCESS;
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
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("d"))
    {
        if(arguments.nbArguments()!=3)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -c keys sbox ciphertext"<<endl;
        }
        Chiffre test(Parseur::parseClefs(arguments.getArgument(0)), Parseur::parseSBox(arguments.getArgument(1)));
        vector<bitset<BLOC_LENGTH>> plaintext=test.dechiffrer(Parseur::parseText(arguments.getArgument(2)));
        for(bitset<BLOC_LENGTH> bloc : plaintext)
            cout<<bloc;
        return EXIT_SUCCESS;
    }
    cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
    return 0;
}
