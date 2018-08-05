#include <iostream>
#include <fstream>
#include <sstream>
#include "vm_parser.hpp"

int main(int argc, char *argv[]){
	// Open arg 1 as file
	std::ifstream inputFileStream(argv[1]);
	std::stringstream buffer;
	buffer << inputFileStream.rdbuf();

	std::string vmCode = buffer.str();

	if (vmCode.empty()) {
		std::cerr << "ERROR: VM file is empty or does not exist" << std::endl;
		return EXIT_FAILURE;
	}

    VMParser parser;

    parser.Initialize(vmCode);

    while (parser.HasMoreCommands()) {
		std::string command = parser.GetCurrentCommand();

		VMCommandType type = parser.GetCommandType(command);
        
		std::string arg1 = parser.Arg1(command);
		std::string arg2 = parser.Arg2(command);
		
		std::cout << "arg1: " << arg1 << " | arg 2: " << arg2 << std::endl;

		switch (type) {
			case VMCommandType::C_ARITHMETIC:
				break;
			case VMCommandType::C_POP:
				break;
			case VMCommandType::C_PUSH:
				break;
		}

		parser.NextCommand();
    }

    // std::string asmCode;

	// std::ofstream outputFileStream("a.asm");

	// outputFileStream << asmCode;

	// std::cout << "SUCCESS: Translated VM file" << std::endl;

	return EXIT_SUCCESS;
}