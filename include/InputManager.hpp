#pragma once

#include <SDL.h>
#include "Vector2.hpp"

class InputManager
{
private:
	SDL_Scancode leftKey, rightKey;
	const Uint8* keyboardState;
	SDL_GameController* controller;
	SDL_Joystick* joystick;
	int joystickInstanceId;
public:
	InputManager();
	~InputManager();

	void setInputs(SDL_Scancode leftKey, SDL_Scancode rightKey);

	void update();

	float getAxis();
	bool buttonDown(SDL_Scancode key, SDL_GameControllerButton button = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID);
};
