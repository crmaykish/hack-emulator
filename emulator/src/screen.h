#include <SDL2/SDL.h>
#include "cpu.h"

static const int SCREEN_WIDTH = 512;
static const int SCREEN_HEIGHT = 256;
static const int SCREEN_BUFFER = 0x4000;

typedef struct Screen {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Screen;

int create_screen(Screen *screen);
void render(Screen *screen, CPU *cpu);
void destroy_screen(Screen *screen);