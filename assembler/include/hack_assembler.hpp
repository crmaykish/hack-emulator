#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <string>
#include "hack_parser.hpp"

class HackAssembler {
public:
    /**
     * @brief Assemble ASM code into machine code
     * 
     * @param assembly ASM code in string format
     * @return std::string Binary machine code in ASCII format, each line is one instruction
     */
    std::string Assemble(std::string assembly);

private:
    HackParser Parser;
};

#endif