typedef struct Parser {
	char *file_contents;
	int line_count;
	char *current_command;
	unsigned int current_command_loc;
	char **command_list;
} Parser;

typedef enum {A_COMMAND, C_COMMAND, L_COMMAND} Command_Type;

void parser_init(Parser *parser, char *file_contents);

int has_more_commands(Parser *parser);
char *load_next_command(Parser *parser);

Command_Type command_type(Parser *parser);

char *symbol(Parser *parser);
char *dest(Parser *parser);
char *comp(Parser *parser);
char *jump(Parser *parser);

unsigned int line_count(Parser *p);