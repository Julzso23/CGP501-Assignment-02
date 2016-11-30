#include "LevelManager.hpp"

LevelManager::LevelManager(Player& player, std::vector<std::string> levelNames, SDL_Renderer* renderer)
{
	loadLevels(levelNames, renderer);
	shuffle();
	player.setPosition(levels.front()->getPlayerStart());
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
	std::random_shuffle(levels.begin(), levels.end());
}

void LevelManager::draw(Vector2f cameraPosition)
{
	levels.front()->draw(cameraPosition);
}

void LevelManager::updateCollisions(Player& player)
{
	levels.front()->updateCollisions(player);
}
