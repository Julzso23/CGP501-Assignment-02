#include "LevelManager.hpp"

LevelManager::LevelManager(std::vector<std::string> levelNames, SDL_Renderer* renderer) :
    randomEngine(randomDevice())
{
    loadLevels(levelNames, renderer);
    shuffle();
}

void LevelManager::loadLevels(std::vector<std::string> levelNames, SDL_Renderer* renderer)
{
    for (std::string& name : levelNames)
    {
        levels.push_back(std::move(std::make_shared<Level>(name, renderer)));
    }
}

void LevelManager::shuffle()
{
    std::shuffle(levels.begin(), levels.end(), randomEngine);
}

void LevelManager::nextLevel()
{
    std::shared_ptr<Level> level = levels.front();
    level->load();
    levels.pop_front();
    levels.push_back(level);
}

std::shared_ptr<Level> LevelManager::getCurrent()
{
    return levels.front();
}
