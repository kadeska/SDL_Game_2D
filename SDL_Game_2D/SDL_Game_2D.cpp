// SDL_Game_2D.cpp : Defines the entry point for the application.
//

#include "SDL_Game_2D.hpp"

#include <chrono>


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
	resources.load(state);

	// setup game data
	
	// create out player
	GameObject player;
	player.type = ObjectType::Player;
	player.texture = resources.texIdle;
	player.animations = resources.playerAnims;
	player.currentAnimation = resources.ANIM_PLAYER_IDLE;
	state.gs.layers[LAYER_IDL_CHARACTERS].push_back(player);
	

	// start game loop
	if (!mainGameLoop(state)) { 
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error in main game loop", state.window);
		std::cout << "Game loop closed" << std::endl;
		return 0; 
	}
	

	//SDL_DestroyTexture(texIdle);
	resources.unload();
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
	const bool* keys = SDL_GetKeyboardState(nullptr);
	auto lastFrameTime = std::chrono::high_resolution_clock::now();

	//uint64_t prevTime = SDL_GetTicks();
	//prevTime = SDL_GetTicks();
	bool running = true;
	while (running)
	{
		auto currentFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> deltaTimeDuration = currentFrameTime - lastFrameTime;
		float deltaTime = deltaTimeDuration.count();
		lastFrameTime = currentFrameTime;

		//uint64_t nowTime = SDL_GetTicks();
		//float deltaTime = nowTime - prevTime / 20000.0f; // convert to seconeds
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

		// update all objects
		for (auto& layer : state.gs.layers)
		{
			for (GameObject& obj : layer)
			{
				if (obj.currentAnimation != -1)
				{
					obj.animations[obj.currentAnimation].step(deltaTime);
				}
			}
		}

		// draw commands
		SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255); // set clear color
		SDL_RenderClear(state.renderer); // clear screen

		// draw all objects
		for (auto& layer : state.gs.layers)
		{
			for (GameObject& obj : layer)
			{
				drawObject(state, state.gs, obj, deltaTime);
			}
		}

		//const float floor = state.logH;
		

		// swap buffers and present
		SDL_RenderPresent(state.renderer);
		//prevTime = nowTime;

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

void drawObject(const SDLState& state, GameState& gs, GameObject& obj, float deltaTime)
{
	const float spriteSize = 32;
	float srcX = obj.currentAnimation != -1 ? 
		obj.animations[obj.currentAnimation].currentFrame() * spriteSize : 0;
	SDL_FRect src{ 
		.x = srcX, 
		.y = 0, 
		.w = spriteSize, 
		.h = spriteSize 
	};
	SDL_FRect dst{ 
		.x = obj.position.x, 
		.y = obj.position.y, 
		.w = spriteSize, 
		.h = spriteSize 
	};
	// draw texture
	//SDL_RenderTexture(state.renderer, texIdle, &src, &dst); 
	SDL_FlipMode flipMode = obj.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderTextureRotated(state.renderer, obj.texture, &src, &dst, 0, nullptr, flipMode);
}
