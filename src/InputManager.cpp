#include "InputManager.hpp"

InputManager::InputManager() :
	leftKey(SDL_SCANCODE_UNKNOWN),
	rightKey(SDL_SCANCODE_UNKNOWN)
{
}

void InputManager::setInputs(SDL_Scancode leftKey, SDL_Scancode rightKey)
{
	this->leftKey = leftKey;
	this->rightKey = rightKey;
}

float InputManager::getAxis()
{
	int numKeys;
	const Uint8* keyboardState = SDL_GetKeyboardState(&numKeys);

	if (keyboardState[leftKey])
	{
		return -1.f;
	}

	if (keyboardState[rightKey])
	{
		return 1.f;
	}

	return 0.f;
}
