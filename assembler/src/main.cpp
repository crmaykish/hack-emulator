#include <iostream>
#include "hack_assembler.hpp"

int main(int argc, char *argv[]){

	HackAssembler assembler;

	std::string assemblyCode = "(START)\n@R0\nD=M\n@R1\nD=D-M\n(END)\n@R1\n";

	std::string machineCode = assembler.Assemble(assemblyCode);

	std::cout << machineCode << std::endl;

	// char *asm_file_name = argv[1];
	// char *hack_file_name = argv[2];
	// char *machine_code;
	// FILE *hack_file;
	
	// Primitive argument checking
	// if (argc < 3) {
	// 	std::cout << "Missing arguments..." << std::endl;
	// 	return 1;
	// }

	// assembler = Assembler_Create(asm_file_name);

	// machine_code = Assembler_Assemble(assembler);

	// printf("Machine code:\n%s\n", machine_code);

	// hack_file = fopen(hack_file_name, "w+");

	// fprintf(hack_file, "%s", machine_code);

	// fclose(hack_file);
}