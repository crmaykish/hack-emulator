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
int c_a(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);
int cycle();
void debug();

int main(){
	// TODO: Load ROM

	int running = 1;

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
		int val;
		int store;
		int j;

		// C Instruction
		int a = c_a(OP);
		int comp = c_comp(OP);
		int dest = c_dest(OP);
		int jump = c_jump(OP);

		// Compute value
		if (a == 0){
			c0(comp);
		} else {
			c1(comp);
		}
		// Send it to destination

		// Decide where to jump, if at all

	}
	else {
		// A Instruction
		A = a_val(OP);
		status_code = 1;
	}

	return status_code;
}

// C Instructions

int c0(int comp){
	int val;
	switch (comp) {
		case 0b101010 :		// Zero
			val = 0;
			break;
		case 0b111111 :		// One
			val = 1;
			break;
		case 0b111010 :		// Negative One
			val = -1;
			break;
		case 0b001100 :		// D
			val = D;
			break;
		case 0b110000 :		// A
			val = A;
			break;
		case 0b001101 :		// !D
			val = !D;
			break;
		case 0b110011 : 	// !A
			val = !A;
			break;
		case 0b011111 :		// D+1
			val = D + 1;
			break;
		case 0b110111 : 	// A+1
			val = A + 1;
			break;
		case 0b001110 :		// D-1
			val = D - 1;
			break;
		case 0b110010 :		// A-1
			val = A - 1;
			break;
		case 0b000010 : 	// D+A
			val = D + A;
			break;
		case 0b010011 :		// D-A
			val = D - A;
			break;
		case 0b000111 :
			val = A - D;	// A-D
			break;
		case 0b000000 :
			val = D & A;	// D&A
			break;
		case 0b010101 :
			val = D | A;	// D|A
			break;
	}

	return val;
}

int c1(){
	int val;
	return val;
}

// *** Op Code Decoding *** //

int a_val(int opcode){
	// The AND is probably not necessary if we've already determined this an A instruction
	return opcode & 0b111111111111111;
}

int c_a(int opcode){
	return (opcode & 0b1000000000000) >> 12;
}

int c_comp(int opcode){
	return (opcode & 0b111111000000) >> 6;
}

int c_dest(int opcode){
	return (opcode & 0b111000) >> 3;
}

int c_jump(int opcode){
	return opcode & 0b111;
}

// ************************ //

// *** Debugging Stuff *** //

void debug(){
	printf("%d => %X | A: %X, D: %X\n", PC, OP, A, D);
	printf("%s\n", "---");
}

// *********************** //