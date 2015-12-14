#include "emulator.h"

void emulator_init(Emulator *emulator){
	// Init CPU and Screen
	cpu_init(&emulator->cpu);
	create_screen(&emulator->screen);
}

void run(Emulator *emulator){
	SDL_Event e;

	while (emulator->cpu.running){
		// Handle input events
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				emulator->cpu.running = 0;
			}
			else if (e.type == SDL_KEYDOWN){
				printf("%d\n", e.key.keysym.sym);
			}
		}

		cycle(&emulator->cpu);

		render(&emulator->screen, &emulator->cpu);
	}
}

void load_rom(Emulator *e, char *rom_file_name){
	FILE *rom_file = fopen(rom_file_name, "r");

	if (!rom_file != 0){
		char instruction[16];
		int char_count = 0;
		int c;
		int i=0;

		while( (c = fgetc(rom_file)) != EOF){
			if (c == '0' || c == '1') {
				instruction[char_count] = c;
				char_count++;
				if (char_count == 16){
					char_count = 0;
					e->cpu.ROM[i] = from_bin(instruction);
					i++;
				}
			}
		}

		fclose(rom_file);
	}
}

// void debug(){
// 	printf("%d => %X | A: %X, D: %X\n", PC, OP, A, D);
// 	printf("%s\n", "---");
// 	printf("%X, %X, %X, %X\n---\n", DM[0x10], DM[0x11], DM[0x12], DM[0x13]);
// }

unsigned short from_bin(char *s){
	return (unsigned short) strtol(s, NULL, 2);
}