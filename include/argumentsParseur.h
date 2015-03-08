#pragma once

#include<string>
#include<vector>
#include<map>

/**
* Parse les arguments et les options fournies lors de l'appel en ligne de commande.
**/

class ArgumentsParser
{
public:
    ArgumentsParser(std::vector<std::string> nomsOptions);
    ~ArgumentsParser(){};
    bool demandeAide();
    std::string getArgument(size_t index);
    static std::vector<std::string> getNomsOptions();
    bool getOption(std::string nom);
    size_t nbArguments(){return arguments.size();};
    void parse(int argc, char* argv[]);
private:
    std::vector<std::string> arguments;
    std::map<std::string, bool> options;
};
