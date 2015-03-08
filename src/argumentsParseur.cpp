#include<iostream>
#include <cstdlib>
#include "../include/argumentsParseur.h"

using namespace std;

/**
* Constitue la liste des options possibles
**/

ArgumentsParser::ArgumentsParser(vector<string> nomsOptions) :
arguments(vector<string>()), options(map<string,bool>())
{
    for(string option : nomsOptions)
        options[option] = false;

    options["h"] = false;
    options["-help"] = false;
}

/**
* Test si l'option -h ou --help est passé
**/

bool ArgumentsParser::demandeAide()
{
    return options["h"] || options["-help"];
}

/**
* Parse les arguments et les options
**/

void ArgumentsParser::parse(int argc, char* argv[])
{
    int compteurArguments = 0;
    for(int i = 1; i < argc; i++)
    {
        if( argv[i][0] == '-' )
        {
            string option = string(argv[i]).substr(1);
            if(options.count(option) == 0)
                cerr << "Option inconnue : " << argv[i] << endl;
            else
                options[option] = true;
        }
        else
        {
            arguments.push_back(argv[i]);
            compteurArguments++;
        }
    }
}

/**
* Renvoie l'argument en position index
**/

string ArgumentsParser::getArgument(size_t index)
{
    return arguments[index];
}

/**
* Teste si l'option nom a été passée.
**/

bool ArgumentsParser::getOption(string nom)
{
    return options[nom];
}

/**
* Liste des options possibles
**/

vector<string> ArgumentsParser::getNomsOptions()
{
    vector<string> liste(6);
    liste[0]="c";
    liste[1]="d";
    liste[2]="a";
    liste[3]="e";
    liste[4]="v";
    liste[5]="b";
    return liste;
}
