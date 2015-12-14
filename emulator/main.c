#include <stdio.h>
#include "emulator.h"

int main(int argc, char *args[]){
	Emulator emulator;
	char *rom_file_name = args[1];

	printf("%s\n", "Initializing...");
	emulator_init(&emulator);

	printf("Loading rom file %s\n", rom_file_name);
	load_rom(&emulator, rom_file_name);

	printf("%s\n", "Emulation started");
	run(&emulator);
}