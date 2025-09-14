// SDL_Game_2D.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height, logW, logH;
};

SDL_Texture* texIdle = nullptr;
float playerX;
//float floor;
float spriteSize;
const bool* keys;
//uint64_t prevTime;

bool initializeSDLWindowAndRenderer(SDLState& state);
bool mainGameLoop(SDLState& state);
void cleanup(SDLState& state);

// TODO: Reference additional headers your program requires here.
