#include "LevelManager.hpp"

LevelManager::LevelManager(std::vector<std::string> levelNames, SDL_Renderer* renderer) :
	randomEngine(randomDevice())
{
	loadLevels(levelNames, renderer);
	shuffle();
}

void LevelManager::loadLevels(std::vector<std::string> levelNames, SDL_Renderer * renderer)
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

void LevelManager::draw(Vector2f cameraPosition)
{
	levels.front()->draw(cameraPosition);
}

Sweep LevelManager::sweepIntersection(AABB& object, Vector2f delta)
{
    return levels.front()->sweepIntersection(object, delta);
}

void LevelManager::nextLevel()
{
	levels.pop_front();
}

std::shared_ptr<Level> LevelManager::getCurrent()
{
	return levels.front();
}
