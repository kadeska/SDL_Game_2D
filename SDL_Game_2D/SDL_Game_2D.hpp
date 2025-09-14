// SDL_Game_2D.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <array>

#include "gameObject.hpp"

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameState gs;
	int width, height, logW, logH;
};

const size_t LAYER_IDL_LEVEL = 0;
const size_t LAYER_IDL_CHARACTERS = 1;

struct GameState
{
	std::array<std::vector<GameObject>, 2> layers;
	int playerIndex;

	GameState()
	{
		playerIndex = 0; // will change when loading maps
	}
};

struct Resources 
{
	const int ANIM_PLAYER_IDLE = 0;
	std::vector<Animation> playerAnims;

	std::vector<SDL_Texture*> textures;
	SDL_Texture* texIdle;

	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filepath) 
	{
		SDL_Texture* tex = IMG_LoadTexture(renderer, filepath.c_str());
		SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
		textures.push_back(tex);
		return tex;
	}

	void load(SDLState& state) 
	{
		playerAnims.resize(5);
		playerAnims[ANIM_PLAYER_IDLE] = Animation(8, 1.6f);

		texIdle = loadTexture(state.renderer, "data/idle.png");
	}

	void unload()
	{
		for (auto tex : textures)
		{
			SDL_DestroyTexture(tex);
		}
		textures.clear();
	}
};

Resources resources;

float playerX;
//float floor;
float spriteSize;
const bool* keys;
//uint64_t prevTime;

bool flipHorizontal = false;

bool initializeSDLWindowAndRenderer(SDLState& state);
bool mainGameLoop(SDLState& state);
void drawObject(const SDLState& state, GameState& gs, GameObject& obj, float deltaTime);
void cleanup(SDLState& state);

// TODO: Reference additional headers your program requires here.
