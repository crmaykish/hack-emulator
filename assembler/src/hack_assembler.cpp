#include "hack_assembler.hpp"
#include <iostream>

std::string HackAssembler::Assemble(std::string assembly) {
	std::string machineCode;

	// Give the assembly code to the parser
	Parser.Initialize(assembly);

	// Initial pass through the code to create symbols
	Parser.CreateLabelSymbols();

	// loop through each assembly command and convert to machine instruction
	while (Parser.HasMoreCommands()) {
		std::string command = Parser.GetCurrentCommand();
		CommandType type = Parser.GetCommandType(command);

		std::string instruction;

		// TODO: make command types into classes and have them implement their own parsing? overkill?
		switch (type) {
			case CommandType::A_COMMAND :
				std::cout << "A       : " << command << std::endl;
				instruction = Parser.ParseA(command);
				machineCode.append(instruction).append("\n");
				break;
			case CommandType::C_COMMAND :
				std::cout << "C       : " << command << std::endl;
				instruction = Parser.ParseC(command);
				machineCode.append(instruction).append("\n");
				break;
			case CommandType::L_COMMAND :
				std::cout << "L       : " << command << std::endl;
				break;
			case CommandType::SKIP :
				std::cout << "SKIP    : " << command << std::endl;
				break;
			case CommandType::INVALID :
				std::cout << "INVALID : " << command << std::endl;
				// TODO: exit on invalid command
				break;
		}

		Parser.NextCommand();
	}

	return machineCode;
}