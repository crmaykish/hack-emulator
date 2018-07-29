#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "parser.h"

typedef struct Assembler Assembler;

Assembler* Assembler_Create();
void Assembler_Destroy(Assembler *assembler);
char* Assembler_Assemble(Assembler *assembler);

#endif