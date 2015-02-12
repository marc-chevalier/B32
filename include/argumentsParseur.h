#pragma once

#include<string>
#include<vector>
#include<map>

class ArgumentsParser
{
public:
    ArgumentsParser(std::vector<std::string> nomsOptions);
    void parse(int argc, char* argv[]);
    std::string getArgument(size_t index);
    size_t nbArguments(){return arguments.size();};
    bool getOption(std::string nom);
    bool demandeAide();
    static std::vector<std::string> getNomsOptions();
private:
    std::vector<std::string> arguments;
    std::map<std::string, bool> options;
};
