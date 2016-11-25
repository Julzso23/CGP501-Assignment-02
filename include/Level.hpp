#pragma once

#include "Transformable.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>

class Level : public Transformable
{
private:
	SDL_Renderer* renderer;

	std::vector<std::shared_ptr<Tile>> tiles;
public:
	Level(std::string fileName, SDL_Renderer* renderer);

	void draw(Vector2f cameraPosition);
	void updateCollisions(Player& player);
};
