#include <iostream>
#include "hack_assembler.hpp"

int main(int argc, char *argv[]){

	HackAssembler assembler;

	std::string assemblyCode = "(START)\n@R0       //crap \nD=M\n@R1     //more crap \nD=D-M\n(END)\n@R1\n";

	std::string machineCode = assembler.Assemble(assemblyCode);

	std::cout << machineCode << std::endl;
}