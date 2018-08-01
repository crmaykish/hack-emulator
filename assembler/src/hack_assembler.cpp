#include "hack_assembler.hpp"
#include <iostream>

HackAssembler::HackAssembler() {

}

HackAssembler::~HackAssembler() {

}

void HackAssembler::LoadASM(std::string) {

}

std::string HackAssembler::Assemble() {

}


// char* load_asm_file(Assembler *a, char *asm_path);

// Assembler* Assembler_Create(char *asm_path){
// 	Assembler *assembler = calloc(1, sizeof(Assembler));

// 	int mach_line_count = 0;
// 	char *file_contents = load_asm_file(assembler, asm_path);
// 	assembler->parser = Parser_Create(file_contents);

// 	mach_line_count = machine_code_line_count(assembler->parser);
// 	assembler->machine_code = calloc(1, sizeof(char) * 17 * mach_line_count);

// 	return assembler;
// }

// void Assembler_Destroy(Assembler *assembler) {
// 	Parser_Destroy(assembler->parser);
// 	free(assembler);
// }

// char* Assembler_Assemble(Assembler *assembler){

// 	Parser_CreateSymbols(assembler->parser);

// 	Parser_Reset(assembler->parser);

// 	while (has_more_commands(assembler->parser)){
// 		char *command = load_next_command(assembler->parser);
// 		Command_Type type = command_type(assembler->parser);
// 		char *machine_code;

// 		switch (type){
// 			case A_COMMAND :
// 				machine_code = a_command(assembler->parser);
// 				strcat(assembler->machine_code, machine_code);
// 				strcat(assembler->machine_code, "\n");
// 				free(machine_code);
// 				break;
// 			// case L_COMMAND :
// 			// 	l_command(assembler->parser);
// 			// 	break;
// 			case C_COMMAND :
// 				machine_code = c_command(assembler->parser);
// 				strcat(assembler->machine_code, machine_code);
// 				strcat(assembler->machine_code, "\n");
// 				free(machine_code);
// 				break;
// 			case SKIP :
// 				break;
// 			case INVALID :
// 				// TODO: Break and exit on bad command
// 				break;
// 		}
// 	}

// 	return assembler->machine_code;
// }

// char* load_asm_file(Assembler *a, char *asm_path){
// 	int status_code = 0;
// 	FILE *asm_file = fopen(asm_path, "r");
// 	char *file_contents;

// 	if (asm_file == NULL){
// 		status_code = 1;
// 	}
// 	else {
// 		long file_length = 0;
// 		char c = 0;

// 		fseek(asm_file, 0, SEEK_END);
// 		file_length = ftell(asm_file);
// 		fseek(asm_file, 0, SEEK_SET);

// 		file_contents = malloc(file_length);

// 		if (file_contents){
// 			fread(file_contents, 1, file_length, asm_file);
// 		}

// 		fclose(asm_file);
// 	}

// 	return file_contents;
// }