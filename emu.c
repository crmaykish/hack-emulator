#include <stdio.h>

int A = 0;		// Address Register
int D = 0;		// Data Register
int IM[32768];	// Instruction Memory (ROM)
int DM[32768];	// Data Memory (RAM)
int PC = 0;		// Program Counter
int OP = 0;		// Latest Op Code

int a_val(int opcode);
int c_a(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);
int c0(int comp);
int c1(int comp);
void jump(int comp, int jump);
void dest(int val, int dest);
void cycle();
void load_rom();
void debug();

int main(){
	load_rom();
	
	while (1){
		cycle();
		debug();
		getchar();
	}

	return 0;
}

void cycle(){
	// Fetch Op Code
	OP = IM[PC];

	// Execute Op Code
	if (OP & 0b1000000000000000){	// C Instruction Type
		// Compute value
		int val = c_a(OP) == 0 ? c0(c_comp(OP)) : c1(c_comp(OP));

		// Store computed value in the specified location(s)
		dest(val, c_dest(OP));

		// Jump to the next specified instruction
		jump(val, c_jump(OP));
	}
	else {	// A Instruction Type
		A = a_val(OP);	// Set A to the value
		PC++;			// Increment program counter
	}
}

// Decide where to jump, if at all
void jump(int comp, int jump){
	switch (jump) {
		case 0b000 : 	// no jump
			PC++;
			break;
		case 0b001 : 	// comp > 0
			if (comp > 0) { PC = A; }
			break;
		case 0b010 : 	// comp = 0
			if (comp == 0) { PC = A; }
			break;
		case 0b011 : 	// comp >= 0
			if (comp >= 0) { PC = A; }
			break;
		case 0b100 : 	// comp < 0
			if (comp < 0) { PC = A; }
			break;
		case 0b101 : 	// comp != 0
			if (comp != 0) { PC = A; }
			break;
		case 0b110 : 	// comp <= 0
			if (comp <= 0) { PC = A; }
			break;
		case 0b111 : 	// unconditional
			PC = A;
			break;
	}
}

// Send value to destination, notice these are not mutually exclusive. 
void dest(int val, int dest){
	if (dest & 0b001){
		// Store in M
		DM[A] = val;
	}
	if ((dest & 0b010) >> 1){
		// Store in D
		D = val;
	}
	if ((dest & 0b100) >> 2){
		// Store in A
		A = val;
	}
}

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

int c1(int comp){
	int val;
	switch (comp){
		case 0b110000 :		// M
			val = DM[A];
			break;
		case 0b110001 :		// !M
			val = !DM[A];
			break;
		case 0b110011 : 	// -M
			val = -DM[A];
			break;
		case 0b110111 :		// M+1
			val = DM[A] + 1;
			break;
		case 0b110010 : 	// M-1
			val = DM[A] - 1;
			break;
		case 0b000010 : 	// D+M
			val = D + DM[A];
			break;
		case 0b010011 : 	// D-M
			val = D - DM[A];
			break;
		case 0b000111 : 	// M-D
			val = DM[A] - D;
			break;
		case 0b000000 : 	// D&M
			val = D & DM[A];
			break;
		case 0b010101 : 	// D|M
			val = D|DM[A];
			break;
	}
	return val;
}

// *** ROM Stuff *** //

void load_rom(){
	int i;
	int demo_rom[] = {0b0000000000010000,0b1110111111001000,0b0000000000010000,0b1111110111001000,0b0000000000000010,0b1110101010000111};

	for (i=0; i<sizeof(demo_rom)/4; i++){
		IM[i] = demo_rom[i];
	}
}

// ***************** //

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
	printf("%X, %X, %X, %X\n---\n", DM[0x10], DM[0x11], DM[0x12], DM[0x13]);
}

// *********************** //