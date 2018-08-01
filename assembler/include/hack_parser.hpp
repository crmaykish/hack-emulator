#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

enum class CommandType {A_COMMAND, C_COMMAND, L_COMMAND, SKIP, INVALID};

class HackParser {
public:
    HackParser();
    ~HackParser();
};



// Parser* Parser_Create(char *file_contents);
// void Parser_Destroy(Parser *parser);

// void Parser_Reset(Parser *parser);

// int has_more_commands(Parser *parser);
// char *load_next_command(Parser *parser);

// Command_Type command_type(Parser *parser);

// char *symbol(Parser *parser, const Command_Type type);
// char *dest(Parser *parser);
// char *comp(Parser *parser);
// char *jump(Parser *parser);

// char *a_command(Parser *p);
// char *l_command(Parser *p);
// char *c_command(Parser *p);

// unsigned int line_count(Parser *p);
// unsigned int machine_code_line_count(Parser *p);

// void Parser_CreateSymbols(Parser *p);

#endif