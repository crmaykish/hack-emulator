#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "binary.h"
#include "str_utils.h"

char* assemble(Assembler *a, char *asm_path){
	char *file_contents = load_asm(a, asm_path);
	parser_init(&a->parser, file_contents);

	while (has_more_commands(&a->parser)){
		char *command = load_next_command(&a->parser);
		Command_Type type = command_type(&a->parser);

		printf("%d. ", a->parser.current_command_loc + 1);

		switch (type){
			case A_COMMAND :
				a_command(&a->parser);
				break;
			case L_COMMAND :
				l_command(&a->parser);
				break;
			case C_COMMAND :
				c_command(&a->parser);
				break;
			case SKIP :
				printf("SKIP \n");
				break;
			case INVALID :
				printf("Bad command \n");
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

void a_command(Parser *p){
	int i;
	char *s = symbol(p, A_COMMAND);

	char bin[17];
	bin[16] = '\0';

	for (i = 15; i >=0; i--){
		bin[i] = (atoi(s) >> (15 - i) & 0b1) == 1 ? '1' : '0';
	}

	printf("A : %s\n", bin);

	free(s);
}

void l_command(Parser *p){
	char *s = symbol(p, L_COMMAND);
	printf("%s\n", s);

	free(s);
}

void c_command(Parser *p){
	int i=0;
	char *d = dest(p);	
	char *c = comp(p);
	char *j = jump(p);

	unsigned short b_d = bin_dest(d);
	unsigned short b_c = bin_comp(c);
	unsigned short b_j = bin_jump(j);

	unsigned short conc = ((0b111 << 13) + (b_c << 6) + (b_d << 3) + b_j) & 0xFFFF;

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