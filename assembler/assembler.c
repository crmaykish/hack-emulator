#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

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