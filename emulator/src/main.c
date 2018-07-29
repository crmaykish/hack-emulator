#include <stdlib.h>
#include <stdio.h>
#include "emulator.h"

int main(int argc, char *args[]){
	char *rom_file_name = args[1];

	printf("%s\n", "Initializing...");
	Emulator *emulator = Emulator_Create();

	printf("Loading rom file %s\n", rom_file_name);
	if (Emulator_LoadROM(emulator, rom_file_name) != 0) {
		printf("Failed to load rom file. Exiting.\n");
		exit(1);
	};

	printf("%s\n", "Emulation started");
	Emulator_Run(emulator);
}