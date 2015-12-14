#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 32768

typedef struct CPU {
	int A;			// Address Register
	int D;			// Data Register
	int ROM[MEM_SIZE];	// Instruction Memory (ROM)
	int RAM[MEM_SIZE];	// Data Memory (RAM)
	int PC;			// Program Counter
	int OP;			// Current Op Code
	int running;	// Processor running state
} CPU;

void cpu_init(CPU *cpu);
void cycle(CPU *cpu);

// Opcode decoding
int a_val(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);

// Opcode processing
void jump(CPU *cpu, int comp, int jump);
void dest(CPU *cpu, int val, int dest);
int comp(CPU *cpu, int comp);

#endif