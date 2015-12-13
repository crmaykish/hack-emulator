#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "str_utils.h"

void parser_init(struct Parser *parser, char *file_contents) {
	int i;

	// Point Parser's file_contents at parameter
	parser->file_contents = file_contents;

	// Count the lines in the file contents
	parser->line_count = line_count(parser);

	// Initialize command list array
	parser->command_list = malloc(parser->line_count * sizeof(char*));

	// Split the file contents into lines, each corresponding to a command
	// Ignore empty or commented lines
	parser->command_list[0] = trim(strtok(parser->file_contents, "\n"));

	for (i = 1; i < parser->line_count; i++){
		parser->command_list[i] = trim(strtok(NULL, "\n"));
	}

	// // Start parsing at the beginning of the file
	parser->current_command_loc = 0;

	// // Start with an empty command
	parser->current_command = 0;
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
		starts_with(parser->current_command, "//")		// Check for comments
	){
		return SKIP;
	}

	if (starts_with(parser->current_command, "@")){
		return A_COMMAND;
	}
	else if (starts_with(parser->current_command, "(")){
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
		return substr(parser->current_command, 1, strlen(parser->current_command) - 1);
	}

	// If L command, return the value between the parentheses
	else if (type == L_COMMAND){
		return substr(parser->current_command, 1, strlen(parser->current_command) - 3);
	}

	return NULL;
}

char *dest(Parser *parser) {
	int i = index_of(parser->current_command, '=');
	if (i >= 0){
		return substr(parser->current_command, 0, i);
	}
	return 0;
}

char *comp(Parser *parser) {
	int comp_start = 0;
	int comp_end = strlen(parser->current_command) - 1;

	int eq_index = index_of(parser->current_command, '=');
	int semi_index = index_of(parser->current_command, ';');

	if (eq_index >= 0){
		comp_start = eq_index + 1;
	}

	if (semi_index >= 0){
		comp_end = semi_index;
	}

	char *temp = substr(parser->current_command, comp_start, comp_end - comp_start);

	return temp;
}

char *jump(Parser *parser) {
	int i = index_of(parser->current_command, ';');
	if (i >= 0){
		return substr(parser->current_command, i + 1, strlen(parser->current_command) - (i + 1));
	}
	return 0;
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