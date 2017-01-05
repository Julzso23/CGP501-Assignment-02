#pragma once

#include "Transformable.hpp"
#include "Tile.hpp"
#include "Entities/Key.hpp"
#include "Entities/Door.hpp"
#include <vector>
#include <memory>

class Enemy;

class Level : public Transformable
{
private:
	std::string fileName;
	SDL_Renderer* renderer;
	std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Key>> keys;
	std::vector<std::shared_ptr<Door>> doors;
	std::vector<std::shared_ptr<Enemy>> enemies;
	Vector2f playerStart;

    static const float tileSize;
public:
	Level(std::string fileName, SDL_Renderer* renderer);

	void load();

	void draw(Vector2f cameraPosition);
    Sweep sweepIntersection(AABB& object, Vector2f delta);
    std::vector<int> getKeyIntersections(AABB& object);
	Sweep sweepDoorIntersection(AABB& object, Vector2f delta);

	Vector2f getPlayerStart();
};
