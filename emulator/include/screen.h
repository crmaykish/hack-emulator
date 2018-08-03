#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include "cpu.h"

static const int SCREEN_WIDTH = 512;
static const int SCREEN_HEIGHT = 256;
static const int SCREEN_BUFFER = 0x4000;
static const int FRAME_TIME = 5;  // ms

typedef struct Screen Screen;

Screen* Screen_Create();
void Screen_Render(Screen *screen, CPU *cpu);
void Screen_Destroy(Screen *screen);

#endif