#include <stdio.h>

// Address Register
int A = 0;

// Data Register
int D = 0;

// Instruction Memory (ROM)
int IM[32768];

// Data Memory (RAM)
int DM[32768];

int comp(int opcode);
int dest(int opcode);
int jump(int opcode);

int main(){
	int running = 1;
	A = 0;
	D = 0;

	printf("%s\n", "Starting emulation...");
	
	while (running){
		running = instruction();
	}

	printf("%s\n", "Emulation stopped.");

	return 0;
}

int instruction(){

	return 0;	// bad instruction
}

int comp(int opcode){
	return (opcode & 0b1111111000000) >> 6;
}

int dest(int opcode){
	return (opcode & 0b111000) >> 3;
}

int jump(int opcode){
	return opcode & 0b111;
}