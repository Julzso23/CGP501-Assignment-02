#pragma once

#include <SDL.h>
#include "Vector2.hpp"

class InputManager
{
private:
	SDL_Scancode leftKey, rightKey;
public:
	InputManager();
	void setInputs(SDL_Scancode leftKey, SDL_Scancode rightKey);

	float getAxis();
};
