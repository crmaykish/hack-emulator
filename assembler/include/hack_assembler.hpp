#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <string>
#include "hack_parser.hpp"

class HackAssembler {
public:
    HackAssembler();
    ~HackAssembler();

    void LoadASM(std::string);
    std::string Assemble();

private:
    HackParser parser;
};

#endif