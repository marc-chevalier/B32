#include <iostream>
#include <cstdlib>
#include <vector>
#include "../include/chiffre.h"
#include "../include/parseur.h"
#include "../include/std.h"
#include "../include/argumentsParseur.h"
#include "../include/linearApproxMatrix.h"
#include "../include/testQuestion5.h"
#include "../include/attack.h"
#include "../include/datas.h"

using namespace std;

extern int Plaintext[100][32];
extern int Ciphertext[100][32];

int main(int argc, char* argv[])
{
    ArgumentsParser arguments(ArgumentsParser::getNomsOptions());
    arguments.parse(argc, argv);

    if(arguments.demandeAide())
    {
        cout<<endl<<"Syntaxes :"<<endl;
        cout<<"    ./B32 -c keys sbox plaintext"<<endl;
        cout<<"    ./B32 -d keys sbox ciphertext"<<endl;
        cout<<"    ./B32 -a sbox"<<endl;
        cout<<"    ./B32 -e keys sbox"<<endl;
        cout<<"    ./B32 -b sbox"<<endl<<endl;
        cout<<"-c               Chiffrer"<<endl;
        cout<<"-d               Déchiffrer"<<endl;
        cout<<"-a               Matrice d'approximation linéaire"<<endl;
        cout<<"-e               Expérience de la question 5"<<endl;
        cout<<"-b               A l'attaque ! Montjoie !"<<endl;
        cout<<"-v               Verbose"<<endl;
        cout<<"-h               Vous y êtes"<<endl;
        cout<<"--help           Vous y êtes"<<endl<<endl;
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("c")) /// Chiffrer
    {
        if(arguments.nbArguments()!=3)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -c keys sbox plaintext"<<endl;
            cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
            return EXIT_FAILURE;
        }
        Chiffre test(Parseur::parseClefs(arguments.getArgument(0)), Parseur::parseSBox(arguments.getArgument(1)));
        vector<bitset<BLOC_LENGTH>> ciphertext=test.chiffrer(Parseur::parseText(arguments.getArgument(2)));
        for(bitset<BLOC_LENGTH> bloc : ciphertext)
            cout<<bloc;
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("d")) /// Déchiffrer
    {
        if(arguments.nbArguments()!=3)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -c keys sbox ciphertext"<<endl;
            cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
            return EXIT_FAILURE;
        }
        Chiffre test(Parseur::parseClefs(arguments.getArgument(0)), Parseur::parseSBox(arguments.getArgument(1)));
        vector<bitset<BLOC_LENGTH>> plaintext=test.dechiffrer(Parseur::parseText(arguments.getArgument(2)));
        for(bitset<BLOC_LENGTH> bloc : plaintext)
            cout<<bloc;
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("a")) /// Matrice d'approximation
    {
        if(arguments.nbArguments()!=1)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -a sbox"<<endl;
            cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
            return EXIT_FAILURE;
        }
        vector<bitset<BLOC_LENGTH>> SBox(Parseur::parseSBox(arguments.getArgument(0)));
        LinearApproxMatrix matrix (SBox);
        cout<<matrix<<endl;
		matrix.printFarthestCouples();
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("e")) /// Question 5
    {
        if(arguments.nbArguments()!=2)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -e keys sbox"<<endl;
            cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
            return EXIT_FAILURE;
        }
        TestQuestion5 test(Parseur::parseClefs(arguments.getArgument(0)), Parseur::parseSBox(arguments.getArgument(1)), 10000);
        test.experiment(arguments.getOption("v"));
        return EXIT_SUCCESS;
    }
    if(arguments.getOption("b")) /// Attaque (break)
    {
        if(arguments.nbArguments()!=1)
        {
            cout<<endl<<"Syntaxe :"<<endl;
            cout<<"./B32 -b sbox"<<endl;
            cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
            return EXIT_FAILURE;
        }
        Attack attack(bitsetFromArray(Plaintext), bitsetFromArray(Ciphertext),Parseur::parseSBox(arguments.getArgument(0)));
        attack.findAllKeys(1);
        return EXIT_SUCCESS;
    }
    cout<<"Faites `./B32 --help' ou `./B32 -h' pour plus d'informations."<<endl;
    return EXIT_FAILURE;
}
