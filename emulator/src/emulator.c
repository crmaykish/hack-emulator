#include "emulator.h"

void emulator_init(Emulator *emulator){
	// Init CPU and Screen
	emulator->cpu = CPU_Create();
	create_screen(&emulator->screen);
}

void run(Emulator *emulator){
	SDL_Event e;

	while (CPU_GetRunning(emulator->cpu)){
		// Handle input events
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				CPU_SetRunning(emulator->cpu, 0);
			}
			else if (e.type == SDL_KEYDOWN){
				printf("%d\n", e.key.keysym.sym);
			}
		}

		CPU_Cycle(emulator->cpu);

		render(&emulator->screen, emulator->cpu);
	}
}

int load_rom(Emulator *e, char *rom_file_name){
	FILE *rom_file = fopen(rom_file_name, "r");

	if (rom_file != 0){
		char instruction[16];
		int char_count = 0;
		int c;
		int i=0;
		int rom[MEM_SIZE];

		memset(rom, 0, MEM_SIZE);

		while( (c = fgetc(rom_file)) != EOF){
			if (c == '0' || c == '1') {
				instruction[char_count] = c;
				char_count++;
				if (char_count == 16){
					char_count = 0;
					rom[i] = from_bin(instruction);
					i++;
				}
			}
		}

		CPU_SetROM(e->cpu, rom);

		fclose(rom_file);
	}
	else {
		return 1;
	}

	return 0;
}

unsigned short from_bin(char *s){
	return (unsigned short) strtol(s, NULL, 2);
}