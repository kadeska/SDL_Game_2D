// SDL_Game_2D.cpp : Defines the entry point for the application.
//

#include "SDL_Game_2D.h"

//using namespace std;

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void cleanup(SDLState& state);


int main(int argc, char* argv[])
{
	SDLState state;

	std::cout << "Hello CMake." << std::endl;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
	}

	// create window
	int width = 800;
	int height = 600;
	state.window = SDL_CreateWindow("SDL3 Game 2D", width, height, 0);
	if(!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating SDL3 window", state.window);
		cleanup(state);
		return 1;
	}

	// create renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating SDL3 renderer", state.window);
		cleanup(state);
		return 1;
	}

	// start game loop
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
			default:
				break;
			}
		}

		// draw commands
		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255); // set clear color
		SDL_RenderClear(state.renderer); // clear screen

		// swap buffers and present
		SDL_RenderPresent(state.renderer);
	}

	cleanup(state);
	return 0;
}

void cleanup(SDLState& state) {
	if (state.window) {
		SDL_DestroyRenderer(state.renderer);
		SDL_DestroyWindow(state.window);
	}
	SDL_Quit();
}
