#include "parser.h"

typedef struct Assembler {
	Parser parser;
	char *machine_code;
} Assembler;

char *load_asm(Assembler *a, char *asm_path);
char *assemble(Assembler *a, char *asm_file);
void a_command(Parser *p);
void l_command(Parser *p);
void c_command(Parser *p);