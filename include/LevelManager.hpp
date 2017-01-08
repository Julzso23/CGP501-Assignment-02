#pragma once

#include "Level.hpp"
#include <deque>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>

class LevelManager
{
private:
    std::deque<std::shared_ptr<Level>> levels;

    std::random_device randomDevice;
    std::mt19937 randomEngine;
public:
    LevelManager(std::vector<std::string> levelNames, SDL_Renderer* renderer);

    void loadLevels(std::vector<std::string> levelNames, SDL_Renderer* renderer);
    void shuffle();

    void nextLevel();

    std::shared_ptr<Level> getCurrent();
};
