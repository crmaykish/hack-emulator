#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"

struct CPU {
	int A;			// Address Register
	int D;			// Data Register
	int PC;			// Program Counter
	int OP;			// Current Op Code
	int running;	// Processor running state
	int ROM[MEM_SIZE];		// Instruction Memory (ROM)
	int RAM[MEM_SIZE];		// Data Memory (RAM)
};

// Opcode decoding
int a_val(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);

// Opcode processing
void jump(CPU *cpu, int comp, int jump);
void dest(CPU *cpu, int val, int dest);
int comp(CPU *cpu, int comp);

CPU* CPU_Create() {
	CPU *cpu = calloc(1, sizeof(CPU));

	cpu->A = 0;
	cpu->D = 0;
	cpu->PC = 0;
	cpu->OP = 0;
	cpu->running = 1;

	return cpu;
}

void CPU_Destroy(CPU *cpu) {
	free(cpu);
}

CPUState CPU_GetRunning(CPU *cpu) {
	return cpu->running;
}

void CPU_SetRunning(CPU *cpu, CPUState running) {
	cpu->running = running;
}

void CPU_SetROM(CPU *cpu, int rom[]) {
	memcpy(cpu->ROM, rom, MEM_SIZE);
}

int* CPU_GetRAM(CPU *cpu) {
	return cpu->RAM;
}

void CPU_Cycle(CPU *cpu) {
	// Fetch Op Code
	cpu->OP = cpu->ROM[cpu->PC];

	// C Instruction Type
	if (cpu->OP & (1 << 15)){	
		// Compute value
		int val = comp(cpu, c_comp(cpu->OP));

		// Store computed value in the destination(s)
		dest(cpu, val, c_dest(cpu->OP));

		// Jump to the next specified instruction
		jump(cpu, val, c_jump(cpu->OP));
	}
	// A Instruction Type
	else {						
		// Set A to the value
		cpu->A = a_val(cpu->OP);
		// Increment program counter	
		cpu->PC++;					
	}

	#if DEBUG == 1
		printf("PC: %d | OP: %X | A: %X | D: %X | M: %X\n", cpu->PC, cpu->OP, cpu->A, cpu->D, cpu->RAM[cpu->A]);
	#endif
}

// Decide where to jump, if at all
void jump(CPU *cpu, int comp, int jump) {
	int jump_flag = 0;
	switch (jump) {
		case 0b000 : 	// no jump
			jump_flag = 0;
			break;
		case 0b001 : 	// comp > 0
			if (comp > 0) { jump_flag = 1; }
			break;
		case 0b010 : 	// comp = 0
			if (comp == 0) { jump_flag = 1; }
			break;
		case 0b011 : 	// comp >= 0
			if (comp >= 0) { jump_flag = 1; }
			break;
		case 0b100 : 	// comp < 0
			if (comp < 0) { jump_flag = 1; }
			break;
		case 0b101 : 	// comp != 0
			if (comp != 0) { jump_flag = 1; }
			break;
		case 0b110 : 	// comp <= 0
			if (comp <= 0) { jump_flag = 1; }
			break;
		case 0b111 : 	// unconditional
			jump_flag = 1;
			break;
	}

	cpu->PC = jump_flag == 1 ? cpu->A : cpu->PC + 1;
}

// Send value to destination, notice these are not mutually exclusive. 
void dest(CPU *cpu, int val, int dest) {	
	if (dest & 0b001){
		cpu->RAM[cpu->A] = val;	// Store in M
	}
	if ((dest & 0b010) >> 1){	// Store in D
		cpu->D = val;
	}
	if ((dest & 0b100) >> 2){	// Store in A
		cpu->A = val;
	}
}

int comp(CPU *cpu, int comp) {
	int val;
	switch (comp) {
		case 0b0101010 :		// Zero
			val = 0;
			break;
		case 0b0111111 :		// One
			val = 1;
			break;
		case 0b0111010 :		// Negative One
			val = -1;
			break;
		case 0b0001100 :		// D
			val = cpu->D;
			break;
		case 0b0110000 :		// A
			val = cpu->A;
			break;
		case 0b0001101 :		// !D
			val = !cpu->D;
			break;
		case 0b0110011 : 		// !A
			val = !cpu->A;
			break;
		case 0b0011111 :		// D+1
			val = cpu->D + 1;
			break;
		case 0b0110111 : 		// A+1
			val = cpu->A + 1;
			break;
		case 0b0001110 :		// D-1
			val = cpu->D - 1;
			break;
		case 0b0110010 :		// A-1
			val = cpu->A - 1;
			break;
		case 0b0000010 : 		// D+A
			val = cpu->D + cpu->A;
			break;
		case 0b0010011 :		// D-A
			val = cpu->D - cpu->A;
			break;
		case 0b0000111 :		// A-D
			val = cpu->A - cpu->D;
			break;
		case 0b0000000 :		// D&A
			val = cpu->D & cpu->A;
			break;
		case 0b0010101 :		// D|A
			val = cpu->D | cpu->A;
			break;
		case 0b1110000 :		// M
			val = cpu->RAM[cpu->A];
			break;
		case 0b1110001 :		// !M
			val = !cpu->RAM[cpu->A];
			break;
		case 0b1110011 : 		// -M
			val = -cpu->RAM[cpu->A];
			break;
		case 0b1110111 :		// M+1
			val = cpu->RAM[cpu->A] + 1;
			break;
		case 0b1110010 : 		// M-1
			val = cpu->RAM[cpu->A] - 1;
			break;
		case 0b1000010 : 		// D+M
			val = cpu->D + cpu->RAM[cpu->A];
			break;
		case 0b1010011 : 		// D-M
			val = cpu->D - cpu->RAM[cpu->A];
			break;
		case 0b1000111 : 		// M-D
			val = cpu->RAM[cpu->A] - cpu->D;
			break;
		case 0b1000000 : 		// D&M
			val = cpu->D & cpu->RAM[cpu->A];
			break;
		case 0b1010101 : 		// D|M
			val = cpu->D|cpu->RAM[cpu->A];
			break;
	}

	return val;
}

int a_val(int opcode) {
	return opcode & 0b111111111111111;
}

int c_comp(int opcode) {
	return (opcode & 0b1111111000000) >> 6;
}

int c_dest(int opcode) {
	return (opcode & 0b111000) >> 3;
}

int c_jump(int opcode) {
	return opcode & 0b111;
}
