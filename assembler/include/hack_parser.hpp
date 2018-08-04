#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include <list>

enum class CommandType {A_COMMAND, C_COMMAND, L_COMMAND, SKIP, INVALID};

static const int RAM_START =            0x0010;

// Registers
static const int PREDEF_R0 =            0x0000;
static const int PREDEF_R1 =            0x0001;
static const int PREDEF_R2 =            0x0002;
static const int PREDEF_R3 =            0x0003;
static const int PREDEF_R4 =            0x0004;
static const int PREDEF_R5 =            0x0005;
static const int PREDEF_R6 =            0x0006;
static const int PREDEF_R7 =            0x0007;
static const int PREDEF_R8 =            0x0008;
static const int PREDEF_R9 =            0x0009;
static const int PREDEF_R10 =           0x000A;
static const int PREDEF_R11 =           0x000B;
static const int PREDEF_R12 =           0x000C;
static const int PREDEF_R13 =           0x000D;
static const int PREDEF_R14 =           0x000E;
static const int PREDEF_R15 =           0x000F;

// Predefined RAM addresses
static const int PREDEF_SP =            0x0000;
static const int PREDEF_LCL =           0x0001;
static const int PREDEF_ARG =           0x0002;
static const int PREDEF_THIS =          0x0003;
static const int PREDEF_THAT =          0x0004;
static const int PREDEF_SCREEN =        0x4000;
static const int PREDEF_KBD =           0x6000;

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

    std::string Dest(std::string command);
    std::string Comp(std::string command);
    std::string Jump(std::string command);
};

#endif