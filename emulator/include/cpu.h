#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 32768

typedef enum {
	CPU_RUNNING = 1,
	CPU_STOPPED = 0
} CPUState;

typedef struct CPU CPU;

CPU* CPU_Create();

void CPU_Cycle(CPU *cpu);

// TODO: make these private functions
// Opcode decoding
int a_val(int opcode);
int c_comp(int opcode);
int c_dest(int opcode);
int c_jump(int opcode);

// Opcode processing
void jump(CPU *cpu, int comp, int jump);
void dest(CPU *cpu, int val, int dest);
int comp(CPU *cpu, int comp);

CPUState CPU_GetRunning(CPU *cpu);
void CPU_SetRunning(CPU *cpu, CPUState state);

void CPU_SetROM(CPU *cpu, int rom[MEM_SIZE]);

int* CPU_GetRAM(CPU *cpu);

#endif