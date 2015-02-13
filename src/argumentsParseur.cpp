#include<iostream>
#include <cstdlib>
#include "../include/argumentsParseur.h"

using namespace std;

ArgumentsParser::ArgumentsParser(vector<string> nomsOptions) :
arguments(vector<string>()), options(map<string,bool>())
{
    for(string option : nomsOptions)
        options[option] = false;

    options["h"] = false;
    options["-help"] = false;
}

bool ArgumentsParser::demandeAide()
{
    return options["h"] || options["-help"];
}

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

string ArgumentsParser::getArgument(size_t index)
{
    return arguments[index];
}

bool ArgumentsParser::getOption(string nom)
{
    return options[nom];
}

vector<string> ArgumentsParser::getNomsOptions()
{
    vector<string> liste(3);
    liste[0]="c";
    liste[1]="d";
    liste[2]="a";
    return liste;
}
