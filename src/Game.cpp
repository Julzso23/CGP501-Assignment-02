#include "Game.hpp"
#include "Utility.hpp"
#include <Windows.h>
#include <fstream>

void Game::loadConfig(std::string fileName)
{
	char title[128];
	GetPrivateProfileString("window", "title", "Unnamed", title, 128, "./config.ini");
	config.title = title;

	config.fullscreen = GetPrivateProfileInt("window", "fullscreen", 0, "./config.ini") == 1;

	config.size = Vector2i(GetPrivateProfileInt("window", "width", 1280, "./config.ini"),
						   GetPrivateProfileInt("window", "height", 720, "./config.ini"));

	config.monitor = GetPrivateProfileInt("window", "monitor", 0, "./config.ini");
}

void Game::setRenderScale()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // Nearest neighbor scaling
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	// Scale the virtual window size based on the width
	SDL_RenderSetLogicalSize(renderer, config.size.x, (int)floor((config.size.x / (float)width) * height));
}

void Game::setMonitor(int id)
{
	// Take it out of fullscreen and move then move it to the correct monitor
	SDL_SetWindowFullscreen(window, NULL);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(id), SDL_WINDOWPOS_CENTERED_DISPLAY(id));
	// If it's meant to be fullscreen, put it back in fullscreen
	if (config.fullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	setRenderScale();
}

void Game::update(float deltaTime)
{
}

void Game::draw()
{
}

Game::Game() :
	window(nullptr),
	renderer(nullptr),
	running(true),
	lastTime(0)
{
	loadConfig("config.terribleFormat");

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED_DISPLAY(0), SDL_WINDOWPOS_CENTERED_DISPLAY(0), config.size.x, config.size.y, config.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : NULL);
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

	setMonitor(config.monitor);
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
        // Calculate the change in time since the last frame
		float deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		update(deltaTime);

        // Clear the screen with a white background
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		draw();
		SDL_RenderPresent(renderer);
	}

	return 0;
}
