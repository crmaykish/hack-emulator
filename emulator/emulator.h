#include "cpu.h"
#include "screen.h"

static const int KEYBOARD_BUFFER = 0x6000;

typedef struct Emulator {
	CPU cpu;
	Screen screen;
} Emulator;

void emulator_init(Emulator *emulator);
void load_rom(Emulator *emulator, char *rom_file_name);
void run(Emulator *emulator);
unsigned short from_bin(char *s);