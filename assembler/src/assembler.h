#include "parser.h"

typedef struct Assembler {
	Parser parser;
	char *machine_code;
} Assembler;

void assembler_init(Assembler *a, char *asm_path);
char *load_asm(Assembler *a, char *asm_path);
char *assemble(Assembler *a);