#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

int main(int argc, char *argv[]){
	char *asm_file_name = argv[1];
	char *hack_file_name = argv[2];
	char *machine_code;
	Assembler a;
	
	// Primitive argument checking
	if (argc < 3) {
		printf("%s\n", "Missing arguments...");
		return 1;
	}

	printf("Starting assembly of %s\n", asm_file_name);
	machine_code = assemble(&a, asm_file_name);

	// TODO: Write machine code to file
}