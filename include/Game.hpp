#pragma once

#define SDL_MAIN_HANDLED

#include "Vector2.hpp"
#include <SDL.h>
#include <string>

class Game
{
private:
	bool running;
	Uint64 lastTime;
protected:
	SDL_Window* window;
	SDL_Renderer* renderer;

	virtual void update(float deltaTime);
	virtual void draw();
public:
	Game(std::string title, Vector2i size, Uint32 flags);
	virtual ~Game();

	int run();
};