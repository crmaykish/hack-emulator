#include "vm_parser.hpp"
#include <iostream>

VMParser::VMParser() {
    std::cout << "Constructing VM Parser" << std::endl;
}

VMCommandType VMParser::GetCommandType(std::string command) {
    if (!command.empty()) {
        // ARITHMETIC commands
        if (command.substr(0, 3) == "add" || 
            command.substr(0, 3) == "sub" || 
            command.substr(0, 3) == "neg" || 
            command.substr(0, 2) == "eq" || 
            command.substr(0, 2) == "gt" || 
            command.substr(0, 2) == "lt" || 
            command.substr(0, 3) == "and" ||
            command.substr(0, 2) == "or" || 
            command.substr(0, 3) == "not") {
            return VMCommandType::C_ARITHMETIC;
        }

        // PUSH
        if (command.substr(0, 4) == "push") {
            return VMCommandType::C_PUSH;
        }

        // POP
        if (command.substr(0, 3) == "pop") {
            return VMCommandType::C_POP;
        }

        // TODO: implement remaining command types

    }

    return VMCommandType::SKIP;
}

std::string VMParser::Arg1(std::string command) {
    int firstSpaceAt = command.find(' ');
    
    if (firstSpaceAt >= 0) {
        return command.substr(0, firstSpaceAt);
    }
    
    return command;
}

std::string VMParser::Arg2(std::string command) {
    int firstSpaceAt = command.find(' ');

    if (firstSpaceAt >= 0){
        return command.substr(firstSpaceAt + 1, command.length() - firstSpaceAt);
    }

    return "";
}