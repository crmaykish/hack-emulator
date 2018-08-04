#include "command_parser.hpp"

#include <iostream>
#include <sstream>
#include <cstring>

std::string trim(std::string str);

void CommandParser::Initialize(std::string code) {
	// Break down code into commands
	std::stringstream st(code);
	std::string line;

	if (!code.empty()) {
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

bool CommandParser::HasMoreCommands() {
	return CommandsIterator != Commands.end();
}

std::string CommandParser::GetCurrentCommand() {
	return *CommandsIterator;
}

void CommandParser::NextCommand() {
	std::advance(CommandsIterator, 1);
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