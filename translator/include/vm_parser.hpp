#ifndef VM_PARSER_HPP
#define VM_PARSER_HPP

#include "command_parser.hpp"
#include <string>
#include <list>

enum class VMCommandType {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, SKIP};

class VMParser : public CommandParser{
public:
    VMParser();

    VMCommandType GetCommandType(std::string command);

    std::string Arg1(std::string command);
    std::string Arg2(std::string command);

private:
    
};

#endif