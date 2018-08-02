#include "hack_parser.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

// Public Functions

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
				Commands.push_back(line);
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
	return "c";
}

std::string HackParser::ParseL(std::string lCommand) {
	return "l";
}

// std::string found = Symbols.find("START")->first;

bool HackParser::HasSymbol(std::string key) {
	return Symbols.count(key) > 0;
}


// char *symbol(Parser *parser, const Command_Type type) {
// 	// If A command, return the value after the @
// 	if (type == A_COMMAND){
// 		return String_Substring(parser->current_command, 1, strlen(parser->current_command) - 1);
// 	}

// 	// If L command, return the value between the parentheses
// 	else if (type == L_COMMAND){
// 		return String_Substring(parser->current_command, 1, strlen(parser->current_command) - 2);
// 	}

// 	return NULL;
// }

// char *dest(Parser *parser) {
// 	int i = String_IndexOf(parser->current_command, '=');
// 	if (i >= 0){
// 		return String_Substring(parser->current_command, 0, i);
// 	}
// 	return 0;
// }

// char *comp(Parser *parser) {
// 	int comp_start = 0;
// 	int comp_end = strlen(parser->current_command) - 1;

// 	int eq_index = String_IndexOf(parser->current_command, '=');
// 	int semi_index = String_IndexOf(parser->current_command, ';');

// 	if (eq_index >= 0){
// 		comp_start = eq_index + 1;
// 	}

// 	if (semi_index >= 0){
// 		comp_end = semi_index;
// 	}

// 	char *temp = String_Substring(parser->current_command, comp_start, comp_end - comp_start);

// 	return temp;
// }

// char *jump(Parser *parser) {
// 	int i = String_IndexOf(parser->current_command, ';');
// 	if (i >= 0){
// 		return String_Substring(parser->current_command, i + 1, strlen(parser->current_command) - (i + 1));
// 	}
// 	return 0;
// }

// // return has to be freed
// char *a_command(Parser *p){
// 	int i;
// 	char *s = symbol(p, A_COMMAND);
// 	char *bin = malloc(17);
// 	bin[16] = '\0';

// 	p->current_command = "@COLIN";
// 	char *a = symbol(p, A_COMMAND);
// 	printf("a: %s\n", a);
// 	printf("a len: %d\n", strlen(a));

// 	p->current_command = "(COLIN)";
// 	char *l = symbol(p, L_COMMAND);
// 	printf("l: %s\n", l);
// 	printf("l len: %d\n", strlen(l));


// 	if (!(String_StartsWith(s, "0") ||
// 		String_StartsWith(s, "1") ||
// 		String_StartsWith(s, "2") ||
// 		String_StartsWith(s, "3") ||
// 		String_StartsWith(s, "4") ||
// 		String_StartsWith(s, "5") ||
// 		String_StartsWith(s, "6") ||
// 		String_StartsWith(s, "7") ||
// 		String_StartsWith(s, "8") ||
// 		String_StartsWith(s, "9")))
// 	{
// 		// value is a symbol
// 		// is it already stored?

// 		printf("s len: %d\n", strlen(s));

// 		printf("symbol: %s\n", s);

// 		int result = SymbolTable_Get(p->symbol_table, s);

// 		printf("result: %d\n", result);

// 	}






// 	// else {
// 	// 	// lookup symbol is symbol table
// 	// 	int symbol_value = SymbolTable_Get(p->symbol_table, s);
// 	// 	if (symbol_value != NO_SYMBOL) {
// 	// 		// use stored symbol value
// 	// 		printf("found it\n");
// 	// 		sprintf(s, "%d", symbol_value);
// 	// 	}
// 	// 	else {
// 	// 		// new symbol - find a spot in memory for it
// 	// 		char* new_symbol = malloc(strlen(s));
// 	// 		// TODO: this has to get freed somewhere

// 	// 		strncpy(new_symbol, s, strlen(new_symbol));

// 	// 		SymbolTable_Add(p->symbol_table, new_symbol, p->ram_loc);

// 	// 		// Use the ram_loc as value now
// 	// 		sprintf(s, "%d", p->ram_loc);

// 	// 		p->ram_loc++;
// 	// 	}
// 	// }

// 	// convert value to binary string
// 	for (i = 15; i >=0; i--){
// 		bin[i] = (atoi(s) >> (15 - i) & 0b1) == 1 ? '1' : '0';
// 	}

// 	free(s);

// 	return bin;
// }

// char *l_command(Parser *p){
// 	char *s = symbol(p, L_COMMAND);

// 	// TODO - lookup the symbol

// 	// printf("Lookup: %s\n", s);


// 	free(s);	// remove this?

// 	return 0;
// }

// char *c_command(Parser *p){
// 	int i=0;
// 	char *d = dest(p);	
// 	char *c = comp(p);
// 	char *j = jump(p);

// 	unsigned short b_d = bin_dest(d);
// 	unsigned short b_c = bin_comp(c);
// 	unsigned short b_j = bin_jump(j);

// 	unsigned short conc = ((0b111 << 13) + (b_c << 6) + (b_d << 3) + b_j) & 0xFFFF;

// 	char *bin = malloc(17);
// 	bin[16] = '\0';

// 	for (i = 15; i >=0; i--){
// 		bin[i] = (conc >> (15 - i) & 0b1) == 1 ? '1' : '0';
// 	}

// 	free(d);
// 	free(c);
// 	free(j);

// 	return bin;
// }
