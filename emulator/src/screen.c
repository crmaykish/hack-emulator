#include "screen.h"

struct Screen {
	SDL_Window *window;
	SDL_Renderer *renderer;
};

Screen* Screen_Create(){
	Screen *screen = (Screen *) calloc(1, sizeof(Screen));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		// return 3;
	}
	
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &screen->window, &screen->renderer)){
		printf("Couldn't create window and renderer: %s\n", SDL_GetError());
		// return 3;
	}

	return screen;
}

void Screen_Render(Screen *screen, CPU *cpu){
	int r, c;
	
	// Set background color
	SDL_SetRenderDrawColor(screen->renderer, 0x00, 0x00, 0x00, 0xFF);
	// Clear screen
	SDL_RenderClear(screen->renderer);
	// Set foreground color
	SDL_SetRenderDrawColor(screen->renderer, 0x00, 0xFF, 0x10, 0xFF);

	// Render from screen buffer
	for (r = 0; r < SCREEN_HEIGHT; r++){
		for (c = 0; c < SCREEN_WIDTH; c++){
			unsigned char bit = (CPU_GetRAM(cpu))[SCREEN_BUFFER + (r * 32) + (c / 16)] % 16;
			if (bit){
				SDL_RenderDrawPoint(screen->renderer, c, r);
			}
		}
	}
	
	SDL_RenderPresent(screen->renderer);

	SDL_Delay(FRAME_TIME);
}

void Screen_Destroy(Screen *screen){
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}