#pragma	once
#include <glm/glm.hpp>
#include <vector>
#include <SDL3/SDL.h>

#include "animation.hpp"

enum class ObjectType
	{
	Player,
	level,
	Enemy
};

struct GameObject
{
	ObjectType type;
	glm::vec2 position, velocity, acceleration;
	float direction;
	std::vector<Animation> animations;
	int currentAnimation;
	SDL_Texture* texture;

	GameObject()
	{
		type = ObjectType::level;
		direction = 1;
		position = velocity = acceleration = glm::vec2(0);
		currentAnimation = -1;
		texture = nullptr;
	}
};