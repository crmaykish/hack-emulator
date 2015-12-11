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

	// Start parsing at the beginning of the file
	parser->current_command_loc = 0;

	// Start with an empty command
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
	if (type == A_COMMAND){
		return parser->current_command + 1;
	}
	else if (type == L_COMMAND){
		
	}

	return NULL;
}

char *dest(Parser *parser) {

}

char *comp(Parser *parser) {

}

char *jump(Parser *parser) {

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