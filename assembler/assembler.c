#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "str_utils.h"

char *file_contents;

int load_asm(char *asm_path);

int main(int argc, char *argv[]){
	// Primitive argument checking
	if (argc < 2) {
		printf("%s\n", "Invalid arguments.");
		return 1;
	}

	if (load_asm(argv[1])){
		printf("%s\n", "Problem loading ASM file.");
		return 1;
	}

	Parser p;
	parser_init(&p, file_contents);

	while (has_more_commands(&p)){
		char *command = load_next_command(&p);
		Command_Type type = command_type(&p);

		printf("%d ", p.current_command_loc + 1);

		if (type == A_COMMAND){
			char *s = symbol(&p, type);
			printf("A: %s\n", s);
			free(s);
		}
		else if (type == L_COMMAND){
			char *s = symbol(&p, type);
			printf("L: %s\n", s);
			free(s);
		}
		else if (type == C_COMMAND){
			char *d = dest(&p);
			char *j = jump(&p);
			char *c = 0;
			printf("C: %s=%s;%s\n", d, c, j);
			free(d);
			free(j);
			free(c);
		}
		else if (type == SKIP){
			printf("SKIP \n");
		}
		else {
			// Invalid command
			printf("Bad command \n");
		}

	}

	return 0;
}

int load_asm(char *asm_path){
	int status_code = 0;
	FILE *asm_file = fopen(asm_path, "r");

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

	return status_code;
}