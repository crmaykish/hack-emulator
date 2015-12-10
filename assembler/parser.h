typedef struct Parser {
	char *file_contents;
	char *current_command;
} Parser;

typedef enum {A_COMMAND, C_COMMAND, L_COMMAND} Command_Type;

void parser_init(Parser *parser, char *file_contents);	// Is it easier to load the whole file into memory than to read it line by line through the file API?

int has_more_commands(Parser *parser);
void advance(Parser *parser);

Command_Type command_type(Parser *parser);

char *symbol(Parser *parser);
char *dest(Parser *parser);
char *comp(Parser *parser);
char *jump(Parser *parser);