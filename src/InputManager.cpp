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

void InputManager::update()
{
	int numKeys;
	keyboardState = SDL_GetKeyboardState(&numKeys);
}

float InputManager::getAxis()
{
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

bool InputManager::keyDown(SDL_Scancode key)
{
	return keyboardState[key];
}
