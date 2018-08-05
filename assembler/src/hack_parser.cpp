#include "hack_parser.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

extern "C" {
	#include "hack_binary.h"
}

HackParser::HackParser() {
	RamPosition = RAM_START;

	// Add predefined symbols
	Symbols.insert(std::pair<std::string, int>("SP", PREDEF_SP));
	Symbols.insert(std::pair<std::string, int>("LCL", PREDEF_LCL));
	Symbols.insert(std::pair<std::string, int>("ARG", PREDEF_ARG));
	Symbols.insert(std::pair<std::string, int>("THIS", PREDEF_THIS));
	Symbols.insert(std::pair<std::string, int>("THAT", PREDEF_THAT));
	Symbols.insert(std::pair<std::string, int>("SCREEN", PREDEF_SCREEN));
	Symbols.insert(std::pair<std::string, int>("KBD", PREDEF_KBD));
	Symbols.insert(std::pair<std::string, int>("R0", PREDEF_R0));
	Symbols.insert(std::pair<std::string, int>("R1", PREDEF_R1));
	Symbols.insert(std::pair<std::string, int>("R2", PREDEF_R2));
	Symbols.insert(std::pair<std::string, int>("R3", PREDEF_R3));
	Symbols.insert(std::pair<std::string, int>("R4", PREDEF_R4));
	Symbols.insert(std::pair<std::string, int>("R5", PREDEF_R5));
	Symbols.insert(std::pair<std::string, int>("R6", PREDEF_R6));
	Symbols.insert(std::pair<std::string, int>("R7", PREDEF_R7));
	Symbols.insert(std::pair<std::string, int>("R8", PREDEF_R8));
	Symbols.insert(std::pair<std::string, int>("R9", PREDEF_R9));
	Symbols.insert(std::pair<std::string, int>("R10", PREDEF_R10));
	Symbols.insert(std::pair<std::string, int>("R11", PREDEF_R11));
	Symbols.insert(std::pair<std::string, int>("R12", PREDEF_R12));
	Symbols.insert(std::pair<std::string, int>("R13", PREDEF_R13));
	Symbols.insert(std::pair<std::string, int>("R14", PREDEF_R14));
	Symbols.insert(std::pair<std::string, int>("R15", PREDEF_R15));
}

void HackParser::CreateLabelSymbols() {
	int codeRow = 0;

	for (std::string& i : Commands) {
		// For each command, check if it's a label, i.e. starts and ends with ()
		if (i.c_str()[0] == '(') {
			if (i.c_str()[i.length() - 1] == ')') {
				// If the commands ends with a ), it's a good label
				Symbols.insert(std::pair<std::string, int>(i.substr(1, i.length() - 2), codeRow));
			}
			else {
				// TODO: Incomplete symbol - error out
			}
		}

		CommandType t = GetCommandType(i);

		if (t == CommandType::A_COMMAND || t == CommandType::C_COMMAND) {
			codeRow++;
		}
	}
}
CommandType HackParser::GetCommandType(std::string command) {
	// Skip comments and empty lines
	if (command.empty() || command.substr(0, 2) == "//") {
		return CommandType::SKIP;
	}
	// A commands start with @
	if (command.substr(0, 1) == "@") {
		return CommandType::A_COMMAND;
	}
	// L commands start with (
	if (command.substr(0, 1) == "(") {
		return CommandType::L_COMMAND;
	}
	// C commands contain = or ;
	if (command.find('=') > 0 || command.find(';')) {
		return CommandType::C_COMMAND;
	}

	return CommandType::INVALID;
}

std::string HackParser::ParseA(std::string aCommand) {
	// A command value
	int value;
	
	// Remove the starting @ to get the symbol
	std::string symbol = aCommand.substr(1, aCommand.length() - 1);

	// If the first character is a digit, use the value directly
	if (std::isdigit(symbol.at(0))) {
		value = atoi(symbol.c_str());
	}
	// Else first character is not a digit, it's a symbol
	else {
		// Look up the symbol
		auto i = Symbols.find(symbol);

		// See if the symbol is already mapped
		if (i != Symbols.end()) {
			// Use the value from the symbols table
			value = i->second;
		}
		else {
			// If not mapped, create a new value in the symbols table and use it
			Symbols.insert(std::pair<std::string, int>(symbol, RamPosition));
			
			// Use the current RAM position and increase it for the next symbol
			value = RamPosition++;
		}
	}

	char bin[17];
	std::memset(bin, 0, 17);
	bin[16] = '\0';

	// Convert value to binary instruction
	for (int i = 15; i >=0; i--) {
		bin[i] = (value >> (15 - i) & 0b1) == 1 ? '1' : '0';
	}

	return std::string(bin);
}

std::string HackParser::ParseC(std::string cCommand) {
		int i=0;
		std::string d = Dest(cCommand);	
		std::string c = Comp(cCommand);
		std::string j = Jump(cCommand);

		unsigned short b_d = bin_dest(d.c_str());
		unsigned short b_c = bin_comp(c.c_str());
		unsigned short b_j = bin_jump(j.c_str());

		unsigned short conc = ((0b111 << 13) + (b_c << 6) + (b_d << 3) + b_j) & 0xFFFF;

		char bin[17];
		std::memset(bin, 0, 17);
		bin[16] = '\0';

		for (i = 15; i >=0; i--){
			bin[i] = (conc >> (15 - i) & 0b1) == 1 ? '1' : '0';
		}

		return std::string(bin);
}

std::string HackParser::Dest(std::string command) {
	int i = command.find('=');

	if (i >= 0) {
		return command.substr(0, i);
	}

	return "";
}

std::string HackParser::Comp(std::string command) {
	int compStart = 0;
	int compEnd = command.length();

	int eqIndex = command.find('=');
	int semiIndex = command.find(';');

	if (eqIndex >= 0) {
		compStart = eqIndex + 1;
	}

	if (semiIndex >= 0) {
		compEnd = semiIndex;
	}

	return command.substr(compStart, compEnd - compStart);
}

std::string HackParser::Jump(std::string command) {
	int i = command.find(';');

	if (i >= 0) {
		return command.substr(i+1, command.length() - (i + 1));
	}

	return "";
}
