#include "InputManager.hpp"
#include <cmath>

InputManager::InputManager() :
    leftKey(SDL_SCANCODE_UNKNOWN),
    rightKey(SDL_SCANCODE_UNKNOWN)
{
    if (SDL_IsGameController(0))
    {
        controller = SDL_GameControllerOpen(0);
        if (controller)
        {
            joystick = SDL_GameControllerGetJoystick(controller);
            joystickInstanceId = SDL_JoystickInstanceID(joystick);
        }
    }
}

InputManager::~InputManager()
{
    SDL_GameControllerClose(controller);
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
    float value = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) / 32768.f;
    if (abs(value) > 0.2f)
    {
        return value;
    }

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

bool InputManager::buttonDown(SDL_Scancode key, SDL_GameControllerButton button)
{
    return keyboardState[key] || SDL_GameControllerGetButton(controller, button);
}
