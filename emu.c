#include <stdio.h>

// Address Register
int A = 0;

// Data Register
int D = 0;

// Instruction Memory (ROM)
int IM[32768];

// Data Memory (RAM)
int DM[32768];

// Program Counter
int PC = 0;

// Latest Op Code
int OP = 0;

int a_val(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);
int cycle();
void debug();

int main(){
	int running = 1;

	IM[0] = 5;

	printf("%s\n", "Starting emulation...");
	
	while (running){
		running = cycle();
		debug();
		PC++;
		getchar();
	}

	printf("%s\n", "Emulation stopped.");

	return 0;
}

int cycle(){
	int status_code = 0;	// 0 = instruction failed, 1 = instruction succeeded

	// Fetch Op Code
	OP = IM[PC];

	// Execute Op Code
	if (OP & 0b1000000000000000){
		// C Instruction
		status_code = 0;
	}
	else {
		// A Instruction
		A = a_val(OP);
		status_code = 1;
	}

	return status_code;
}

int a_val(int opcode){
	// The AND is probably not necessary if we've already determined this an A instruction
	return (opcode & 0b111111111111111);
}

int c_comp(int opcode){
	return (opcode & 0b1111111000000) >> 6;
}

int c_dest(int opcode){
	return (opcode & 0b111000) >> 3;
}

int c_jump(int opcode){
	return opcode & 0b111;
}

void debug(){
	printf("%d => %X | A: %X, D: %X\n", PC, OP, A, D);
	printf("%s\n", "---");
}