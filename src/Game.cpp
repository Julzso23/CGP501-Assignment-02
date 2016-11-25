#include "Game.hpp"
#include <Windows.h>

void Game::update(float deltaTime)
{
}

void Game::draw()
{
}

Game::Game(std::string title, Vector2i size, Uint32 flags) :
	window(nullptr),
	renderer(nullptr),
	running(true),
	lastTime(0)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.x, size.y, flags);
	if (!window)
	{
		MessageBox(NULL, SDL_GetError(), "Window initialisation failed", MB_ICONERROR | MB_OK);
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, NULL);
	if (!renderer)
	{
		MessageBox(NULL, SDL_GetError(), "Renderer initialisation failed", MB_ICONERROR | MB_OK);
		return;
	}
}

Game::~Game()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
}

int Game::run()
{
	if (!window)
		return 1;
	if (!renderer)
		return 1;

	lastTime = SDL_GetPerformanceCounter();

	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_WINDOWEVENT:
				{
					switch (e.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
						{
							running = false;
							break;
						}
					}

					break;
				}
			}
		}

		Uint64 currentTime = SDL_GetPerformanceCounter();
		float deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		update(deltaTime);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		draw();
		SDL_RenderPresent(renderer);
	}

	return 0;
}
