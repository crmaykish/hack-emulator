#include <stdio.h>
#include "emulator.h"

int main(int argc, char *args[]){
	Emulator emulator;

	char *rom_file_name = args[1];

	printf("%s\n", "Initializing...");
	emulator_init(&emulator);

	printf("Loading rom file %s\n", rom_file_name);
	if (load_rom(&emulator, rom_file_name) != 0) {
		printf("Failed to load rom file. Exiting.\n");
		exit(1);
	};

	printf("%s\n", "Emulation started");
	run(&emulator);
}