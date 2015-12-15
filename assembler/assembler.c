#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "binary.h"
#include "str_utils.h"

void assembler_init(Assembler *a, char *asm_path){
	int mach_line_count = 0;
	char *file_contents = load_asm(a, asm_path);
	parser_init(&a->parser, file_contents);

	mach_line_count = machine_code_line_count(&a->parser);
	a->machine_code = malloc((sizeof(char*) * 17) * mach_line_count);
}

char* assemble(Assembler *a){
	while (has_more_commands(&a->parser)){
		char *command = load_next_command(&a->parser);
		Command_Type type = command_type(&a->parser);
		char *machine_code;

		switch (type){
			case A_COMMAND :
				machine_code = a_command(&a->parser);
				strcat(a->machine_code, machine_code);
				strcat(a->machine_code, "\n");
				free(machine_code);
				break;
			case L_COMMAND :
				l_command(&a->parser);
				break;
			case C_COMMAND :
				machine_code = c_command(&a->parser);
				strcat(a->machine_code, machine_code);
				strcat(a->machine_code, "\n");
				free(machine_code);
				break;
			case SKIP :
				break;
			case INVALID :
				// TODO: Break and exit on bad command
				break;
		}
	}

	return a->machine_code;
}

char *load_asm(Assembler *a, char *asm_path){
	int status_code = 0;
	FILE *asm_file = fopen(asm_path, "r");
	char *file_contents;

	if (asm_file == NULL){
		status_code = 1;
	}
	else {
		long file_length = 0;
		char c = 0;

		fseek(asm_file, 0, SEEK_END);
		file_length = ftell(asm_file);
		fseek(asm_file, 0, SEEK_SET);

		file_contents = malloc(file_length);

		if (file_contents){
			fread(file_contents, 1, file_length, asm_file);
		}

		fclose(asm_file);
	}

	return file_contents;
}