#include "hack_parser.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

#include "binary.h"

std::string trim(std::string str);

HackParser::HackParser() {
	RamPosition = 0;
}

void HackParser::Initialize(std::string assemblyCode) {
	// Break down assembly code into commands
	std::stringstream st(assemblyCode);
	std::string line;

	if (!assemblyCode.empty()) {
		while(std::getline(st, line)) {
			if (!line.empty()) {
				// Remove comments
				int commentIndex = line.find("//");
				if (commentIndex >= 0) {
					line = line.substr(0, commentIndex);
				}

				Commands.push_back(trim(line));
			}
		}
	}
	CommandsIterator = Commands.begin();
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
		codeRow++;
	}
}

bool HackParser::HasMoreCommands() {
	return CommandsIterator != Commands.end();
}

std::string HackParser::GetCurrentCommand() {
	return *CommandsIterator;
}

void HackParser::NextCommand() {
	std::advance(CommandsIterator, 1);
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
	if (command.find("=") > 0 || command.find(";")) {
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
		std::map<std::string, int>::iterator i = Symbols.find(symbol);

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

bool HackParser::HasSymbol(std::string key) {
	return Symbols.count(key) > 0;
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

// Copypasted from: http://www.cplusplus.com/forum/beginner/208971/
std::string trim(std::string str) {
	// remove trailing white space
    while( !str.empty() && std::isspace( str.back() ) ) str.pop_back() ;

    // return residue after leading white space
    std::size_t pos = 0 ;
    while( pos < str.size() && std::isspace( str[pos] ) ) ++pos ;
    return str.substr(pos) ;
}