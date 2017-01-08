#pragma once

#define SDL_MAIN_HANDLED

#include "Vector2.hpp"
#include <SDL.h>
#include <string>

class Game
{
public:
    struct Config
    {
        std::string title;
        bool fullscreen;
        Vector2i size;
        int monitor;
    };
private:
    bool running;
    Uint64 lastTime;

    void loadConfig(std::string fileName);
    void setRenderScale();
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Config config;

    void setMonitor(int id);

    virtual void update(float deltaTime);
    virtual void draw();
public:
    Game();
    virtual ~Game();

    int run();
};