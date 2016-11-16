#pragma once

#include <SDL.h>
#include "Vector2.hpp"

class InputManager
{
private:
	SDL_Scancode leftKey, rightKey;
	const Uint8* keyboardState;
public:
	InputManager();
	void setInputs(SDL_Scancode leftKey, SDL_Scancode rightKey);

	void update();

	float getAxis();
	bool keyDown(SDL_Scancode key);
};
