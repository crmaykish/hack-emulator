#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "code.h"
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

		printf("%d. ", p.current_command_loc + 1);

		if (type == A_COMMAND){
			int i;
			char *s = symbol(&p, type);

			char bin[17];
			bin[16] = '\0';

			for (i = 15; i >=0; i--){
				bin[i] = (atoi(s) >> (15 - i) & 0b1) == 1 ? '1' : '0';
			}

			printf("A : %s\n", bin);

			free(s);
		}
		else if (type == L_COMMAND){
			char *s = symbol(&p, type);
			printf("%s\n", s);
			free(s);
		}
		else if (type == C_COMMAND){
			int i=0;
			char *d = dest(&p);	
			char *c = comp(&p);
			char *j = jump(&p);

			unsigned short b_d = bin_dest(d);
			unsigned short b_c = bin_comp(c);
			unsigned short b_j = bin_jump(j);

			unsigned short conc = ((0b111 << 13) + (bin_comp(c) << 6) + (bin_dest(d) << 3) + bin_jump(j)) & 0xFFFF;

			char bin[17];
			bin[16] = '\0';

			for (i = 15; i >=0; i--){
				bin[i] = (conc >> (15 - i) & 0b1) == 1 ? '1' : '0';
			}

			printf("D : %s\n", bin);

			free(d);
			free(c);
			free(j);
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