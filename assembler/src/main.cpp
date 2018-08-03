#include <iostream>
#include <fstream>
#include <sstream>
#include "hack_assembler.hpp"

int main(int argc, char *argv[]){
	// Open arg 1 as file
	std::ifstream inputFileStream(argv[1]);
	std::stringstream buffer;
	buffer << inputFileStream.rdbuf();

	std::string assemblyCode = buffer.str();

	if (assemblyCode.empty()) {
		std::cerr << "ERROR: ASM file is empty or does not exist" << std::endl;
		return EXIT_FAILURE;
	}

	HackAssembler assembler;

	std::string machineCode = assembler.Assemble(assemblyCode);

	std::ofstream outputFileStream("a.hack");

	outputFileStream << machineCode;

	std::cout << "SUCCESS: Assembled HACK file" << std::endl;

	return EXIT_SUCCESS;
}