#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "parser.h"

typedef struct Assembler Assembler;

/**
 * @brief Constructor for Assembler
 * 
 * @param asm_path File path of the ASM source file
 * @return Assembler* 
 */
Assembler* Assembler_Create(char *asm_path);

/**
 * @brief Destructor for Assembler
 * 
 * @param assembler 
 */
void Assembler_Destroy(Assembler *assembler);

/**
 * @brief Assembly language to machine code
 * 
 * @param assembler 
 * @return char* Machine code in a string of 0's and 1's, each line is an instruction
 */
char* Assembler_Assemble(Assembler *assembler);

#endif