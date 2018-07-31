#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "symbol_table.h"
#include "binary.h"
#include "str_utils.h"

struct Parser {
	SymbolTable *symbol_table;
	char *file_contents;
	int line_count;
	char *current_command;
	unsigned int current_command_loc;
	char **command_list;
	int ram_loc;
};

Parser* Parser_Create(char *file_contents) {
	Parser *parser = calloc(1, sizeof(Parser));

	parser->symbol_table = SymbolTable_Create();

	int i;

	// Point Parser's file_contents at parameter
	parser->file_contents = file_contents;

	// Count the lines in the file contents
	parser->line_count = line_count(parser);

	// Initialize command list array
	parser->command_list = malloc(parser->line_count * sizeof(char*));

	// Split the file contents into lines, each corresponding to a command
	parser->command_list[0] = String_Trim(strtok(parser->file_contents, "\n"));

	for (i = 1; i < parser->line_count; i++){
		parser->command_list[i] = String_Trim(strtok(NULL, "\n"));
	}

	// Start parsing at the beginning of the file
	parser->current_command_loc = 0;

	// Start with an empty command
	parser->current_command = 0;

	parser->ram_loc = 0;

	return parser;
}

void Parser_Destroy(Parser *parser) {
	// TODO
	SymbolTable_Destroy(parser->symbol_table);
	free(parser);
}

void Parser_Reset(Parser *parser) {
	parser->current_command = NULL;
	parser->current_command_loc = 0;
}

int has_more_commands(Parser *parser) {
	return parser->current_command_loc < parser->line_count - 1;
}

char *load_next_command(Parser *parser) {
	if (parser->current_command != 0) {
		parser->current_command_loc++;
	}

	parser->current_command = parser->command_list[parser->current_command_loc];

	return parser->current_command;
}

Command_Type command_type(Parser *parser) {

	if (parser->current_command == (char) 0 ||			// Check for empty strings
		isspace(parser->current_command[0]) ||			// Check for empty lines
		String_StartsWith(parser->current_command, "//")		// Check for comments
	){
		return SKIP;
	}

	if (String_StartsWith(parser->current_command, "@")){
		return A_COMMAND;
	}
	else if (String_StartsWith(parser->current_command, "(")){
		return L_COMMAND;
	}
	else if (strstr(parser->current_command, "=") || strstr(parser->current_command, ";")) {
		return C_COMMAND;
	}

	return INVALID;
}

char *symbol(Parser *parser, const Command_Type type) {
	// If A command, return the value after the @
	if (type == A_COMMAND){
		return String_Substring(parser->current_command, 1, strlen(parser->current_command) - 1);
	}

	// If L command, return the value between the parentheses
	else if (type == L_COMMAND){
		return String_Substring(parser->current_command, 1, strlen(parser->current_command) - 3);
	}

	return NULL;
}

char *dest(Parser *parser) {
	int i = String_IndexOf(parser->current_command, '=');
	if (i >= 0){
		return String_Substring(parser->current_command, 0, i);
	}
	return 0;
}

char *comp(Parser *parser) {
	int comp_start = 0;
	int comp_end = strlen(parser->current_command) - 1;

	int eq_index = String_IndexOf(parser->current_command, '=');
	int semi_index = String_IndexOf(parser->current_command, ';');

	if (eq_index >= 0){
		comp_start = eq_index + 1;
	}

	if (semi_index >= 0){
		comp_end = semi_index;
	}

	char *temp = String_Substring(parser->current_command, comp_start, comp_end - comp_start);

	return temp;
}

char *jump(Parser *parser) {
	int i = String_IndexOf(parser->current_command, ';');
	if (i >= 0){
		return String_Substring(parser->current_command, i + 1, strlen(parser->current_command) - (i + 1));
	}
	return 0;
}

char *a_command(Parser *p){
	int i;
	char *s = symbol(p, A_COMMAND);
	char *bin = malloc(17);
	bin[16] = '\0';

	if (String_StartsWith(s, "0") ||
		String_StartsWith(s, "1") ||
		String_StartsWith(s, "2") ||
		String_StartsWith(s, "3") ||
		String_StartsWith(s, "4") ||
		String_StartsWith(s, "5") ||
		String_StartsWith(s, "6") ||
		String_StartsWith(s, "7") ||
		String_StartsWith(s, "8") ||
		String_StartsWith(s, "9"))
	{
		// literal value, just use it
	}
	else {
		// lookup symbol is symbol table
		int symbol_value = SymbolTable_Get(p->symbol_table, s);
		if (symbol_value != NO_SYMBOL) {
			// use stored symbol value
			printf("found it\n");
			sprintf(s, "%d", symbol_value);
		}
		else {
			// new symbol - find a spot in memory for it
			char* new_symbol = malloc(strlen(s));
			// TODO: this has to get freed somewhere

			strncpy(new_symbol, s, strlen(new_symbol));

			SymbolTable_Add(p->symbol_table, new_symbol, p->ram_loc);

			// Use the ram_loc as value now
			sprintf(s, "%d", p->ram_loc);

			p->ram_loc++;
		}
	}

	// convert value to binary string
	for (i = 15; i >=0; i--){
		bin[i] = (atoi(s) >> (15 - i) & 0b1) == 1 ? '1' : '0';
	}

	// free(s);

	return bin;
}

char *l_command(Parser *p){
	char *s = symbol(p, L_COMMAND);

	// TODO - lookup the symbol

	// printf("Lookup: %s\n", s);


	free(s);	// remove this?

	return 0;
}

char *c_command(Parser *p){
	int i=0;
	char *d = dest(p);	
	char *c = comp(p);
	char *j = jump(p);

	unsigned short b_d = bin_dest(d);
	unsigned short b_c = bin_comp(c);
	unsigned short b_j = bin_jump(j);

	unsigned short conc = ((0b111 << 13) + (b_c << 6) + (b_d << 3) + b_j) & 0xFFFF;

	char *bin = malloc(17);
	bin[16] = '\0';

	for (i = 15; i >=0; i--){
		bin[i] = (conc >> (15 - i) & 0b1) == 1 ? '1' : '0';
	}

	free(d);
	free(c);
	free(j);

	return bin;
}

unsigned int line_count(Parser *p){
	unsigned int count = 1;	// Assume last line doesn't have line break after it
	int i;

	for (i = 0; i < strlen(p->file_contents); i++){
		int c = p->file_contents[i];
		if (c == '\n'){
			count++;
		}
	}

	return count;
}

unsigned int machine_code_line_count(Parser *p){
	unsigned int machine_code_line_count = 0;
	int i = 0;

	for (i = 0; i < p->line_count; i++){
		char *com = p->command_list[i];

		if (!(com == (char) 0 ||			// Check for empty strings
			isspace(com[0]) ||					// Check for empty lines
			String_StartsWith(com, "//")			// Check for comments
		)){
			machine_code_line_count++;
		}
	}
	return machine_code_line_count;
}

void Parser_CreateSymbols(Parser *p) {
	int rom_address = 0;

	while (has_more_commands(p)) {
		char *command = load_next_command(p);
		Command_Type type = command_type(p);

		switch (type) {
			case L_COMMAND:
				SymbolTable_Add(p->symbol_table, symbol(p, L_COMMAND), rom_address);
				break;
			case A_COMMAND:
			case C_COMMAND:
				rom_address++;
				break;
			case SKIP:
			case INVALID:
				break;
		}
	}
}