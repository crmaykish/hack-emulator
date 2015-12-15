#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

int main(int argc, char *argv[]){
	char *asm_file_name = argv[1];
	char *hack_file_name = argv[2];
	char *machine_code;
	Assembler a;
	FILE *hack_file;
	
	// Primitive argument checking
	if (argc < 3) {
		printf("%s\n", "Missing arguments...");
		return 1;
	}

	assembler_init(&a, asm_file_name);

	machine_code = assemble(&a);

	printf("Machine code:\n%s\n", machine_code);

	hack_file = fopen(hack_file_name, "w+");

	fprintf(hack_file, "%s", machine_code);

	fclose(hack_file);
}