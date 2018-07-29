#ifndef CPU_H
#define CPU_H

#define MEM_SIZE 32768

typedef struct CPU CPU;

typedef enum {
	CPU_RUNNING = 1,
	CPU_STOPPED = 0
} CPUState;

CPU* CPU_Create();
void CPU_Destroy(CPU *cpu);

CPUState CPU_GetRunning(CPU *cpu);
void CPU_SetRunning(CPU *cpu, CPUState state);

void CPU_SetROM(CPU *cpu, int rom[]);

int* CPU_GetRAM(CPU *cpu);

void CPU_Cycle(CPU *cpu);

#endif