#ifndef PARSER_H
#define PARSER_H

typedef struct Parser {
	char *file_contents;
	int line_count;
	char *current_command;
	unsigned int current_command_loc;
	char **command_list;
} Parser;

typedef enum {A_COMMAND, C_COMMAND, L_COMMAND, SKIP, INVALID} Command_Type;

void parser_init(Parser *parser, char *file_contents);

int has_more_commands(Parser *parser);
char *load_next_command(Parser *parser);

Command_Type command_type(Parser *parser);

char *symbol(Parser *parser, const Command_Type type);
char *dest(Parser *parser);
char *comp(Parser *parser);
char *jump(Parser *parser);

char *a_command(Parser *p);
char *l_command(Parser *p);
char *c_command(Parser *p);

unsigned int line_count(Parser *p);
unsigned int machine_code_line_count(Parser *p);

#endif