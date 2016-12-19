#include "Game.hpp"
#include "Utility.hpp"
#include <Windows.h>
#include <fstream>

void Game::loadConfig(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);

	// Check each line of the config file for config values
	while (file.good())
	{
		std::string line;
		std::getline(file, line);

		std::vector<std::string> elements = Utility::split(line, ':');

		// Trim out any outer whitespace
		elements[0] = Utility::trim(elements[0]);
		elements[1] = Utility::trim(elements[1]);

		if (elements[0] == "title")
		{
			config.title = elements[1];
		}
		else if (elements[0] == "fullscreen")
		{
			config.fullscreen = elements[1] == "true"; // String to bool
		}
		else if (elements[0] == "width")
		{
			config.size.x = std::stoi(elements[1]); // String to int
		}
		else if (elements[0] == "height")
		{
			config.size.y = std::stoi(elements[1]);
		}
		else if (elements[0] == "monitor")
		{
			config.monitor = std::stoi(elements[1]);
		}
	}

	file.close();
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
	config.title = "UnNamed";
	config.fullscreen = false;
	config.size = Vector2i(1280, 720);
	config.monitor = 0;

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
