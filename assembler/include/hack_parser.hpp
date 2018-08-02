#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include <list>

enum class CommandType {A_COMMAND, C_COMMAND, L_COMMAND, SKIP, INVALID};

class HackParser {
public:
    HackParser();

    // TODO: better name
    void Initialize(std::string assemblyCode);

    void CreateLabelSymbols();

    bool HasMoreCommands();
    void NextCommand();
    std::string GetCurrentCommand();
    
    CommandType GetCommandType(std::string command);

    // TODO: Parser should probably not expose command types. Just return a parsed instruction
    std::string ParseA(std::string aCommand);
    std::string ParseC(std::string cCommand);
    std::string ParseL(std::string lCommand);

private:
    std::map<std::string, int> Symbols;
    
    std::list<std::string> Commands;
    std::list<std::string>::iterator CommandsIterator;

    int RamPosition;

    bool HasSymbol(std::string key);
};

// Parser* Parser_Create(char *file_contents);
// void Parser_Destroy(Parser *parser);

// void Parser_Reset(Parser *parser);

// int has_more_commands(Parser *parser);
// char *load_next_command(Parser *parser);

// Command_Type command_type(Parser *parser);

// char *symbol(Parser *parser, const Command_Type type);
// char *dest(Parser *parser);
// char *comp(Parser *parser);
// char *jump(Parser *parser);

// char *a_command(Parser *p);
// char *l_command(Parser *p);
// char *c_command(Parser *p);

// unsigned int line_count(Parser *p);
// unsigned int machine_code_line_count(Parser *p);

// void Parser_CreateSymbols(Parser *p);

#endif