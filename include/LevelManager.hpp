#pragma once

#include "Level.hpp"
#include <deque>
#include <memory>
#include <vector>
#include <algorithm>

class LevelManager
{
private:
	std::deque<std::shared_ptr<Level>> levels;
public:
	LevelManager(Player& player, std::vector<std::string> levelNames, SDL_Renderer* renderer);

	void loadLevels(std::vector<std::string> levelNames, SDL_Renderer* renderer);
	void shuffle();

	void draw(Vector2f cameraPosition);
	void updateCollisions(Player& player);
};
