#ifndef EMULATOR_H
#define EMULATOR_H

static const int KEYBOARD_BUFFER = 0x6000;

typedef struct Emulator Emulator;

Emulator* Emulator_Create();

void Emulator_Destroy(Emulator *emulator);

int Emulator_LoadROM(Emulator *emulator, char *rom_file_name);

void Emulator_Run(Emulator *emulator);

unsigned short from_bin(char *s);

#endif