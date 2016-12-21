#pragma once

#include "Transformable.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Entities/Key.hpp"
#include <vector>
#include <memory>

class Level : public Transformable
{
private:
	SDL_Renderer* renderer;
	std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Key>> keys;
	Vector2f playerStart;
public:
	Level(std::string fileName, SDL_Renderer* renderer);

	void draw(Vector2f cameraPosition);
    Sweep sweepIntersection(AABB& object, Vector2f delta);
    std::vector<int> getKeyIntersections(AABB& object);

	Vector2f getPlayerStart();
};
