#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include <list>

enum class CommandType {A_COMMAND, C_COMMAND, L_COMMAND, SKIP, INVALID};

class HackParser {
public:
    HackParser();

    void Initialize(std::string assemblyCode);

    void CreateLabelSymbols();

    bool HasMoreCommands();
    void NextCommand();
    std::string GetCurrentCommand();
    
    CommandType GetCommandType(std::string command);

    std::string ParseA(std::string aCommand);
    std::string ParseC(std::string cCommand);

private:
    std::map<std::string, int> Symbols;
    
    std::list<std::string> Commands;
    std::list<std::string>::iterator CommandsIterator;

    int RamPosition;

    bool HasSymbol(std::string key);

    std::string Dest(std::string command);
    std::string Comp(std::string command);
    std::string Jump(std::string command);
};

#endif