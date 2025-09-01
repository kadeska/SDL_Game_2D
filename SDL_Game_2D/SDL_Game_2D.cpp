// SDL_Game_2D.cpp : Defines the entry point for the application.
//

#include "SDL_Game_2D.h"

//using namespace std;


int main(int argc, char* argv[])
{
	std::cout << "Hello CMake." << std::endl;

	SDLState state;
	state.width = 1600;
	state.height = 900;
	state.logW = 640;
	state.logH = 320;

	// initialize SDL window and renderer
	if (!initializeSDLWindowAndRenderer(state)) { return 1; }
	
	// load game assets
	texIdle = IMG_LoadTexture(state.renderer, "data/idle.png");
	SDL_SetTextureScaleMode(texIdle, SDL_SCALEMODE_NEAREST);

	// start game loop
	if (!mainGameLoop(state)) { 
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error in main game loop", state.window);
		std::cout << "Game loop closed" << std::endl;
		return 1; 
	}
	

	SDL_DestroyTexture(texIdle);
	cleanup(state);
	return 0;
}

bool initializeSDLWindowAndRenderer(SDLState& state) {
	bool initSuccess = true;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		initSuccess = false;
	}

	// create window
	state.window = SDL_CreateWindow("SDL3 Game 2D", state.width, state.height, SDL_WINDOW_RESIZABLE);
	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating SDL3 window", state.window);
		cleanup(state);
		initSuccess = false;
	}

	// create renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating SDL3 renderer", state.window);
		cleanup(state);
		initSuccess = false;
	}

	// configure presentation

	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	return initSuccess;
}

bool mainGameLoop(SDLState& state) {
	bool running = true;
	while (running)
	{
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				running = false;
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				state.width = event.window.data1;
				state.height = event.window.data2;
				break;
			default:
				break;
			}
		}

		// draw commands
		SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255); // set clear color
		SDL_RenderClear(state.renderer); // clear screen

		SDL_FRect src{ .x = 0, .y = 0, .w = 32, .h = 32 };
		SDL_FRect dst{ .x = 0, .y = 0, .w = 32, .h = 32 };

		SDL_RenderTexture(state.renderer, texIdle, &src, &dst); // draw texture

		// swap buffers and present
		SDL_RenderPresent(state.renderer);
	}

	return running;
}

void cleanup(SDLState& state) {
	if (state.window) {
		SDL_DestroyRenderer(state.renderer);
		SDL_DestroyWindow(state.window);
	}
	SDL_Quit();
}
