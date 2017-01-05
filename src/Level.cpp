#include "Level.hpp"
#include "Utility.hpp"
#include "MovingEnemy.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

const float Level::tileSize = 64.f;

Level::Level(std::string fileName, SDL_Renderer* renderer) :
	fileName(fileName),
	renderer(renderer)
{
	load();
}

void Level::load()
{
	tiles.clear();
	keys.clear();
	doors.clear();

	std::ifstream file;
	file.open("resources/levels/" + fileName + ".level");

    int keyId;

    while (file.good())
    {
        std::string object;
        std::getline(file, object);

        // Skip empty lines
        if (object.empty())
            continue;

        // Split the object into its component parts
        std::vector<std::string> parts = Utility::split(object, ',');

        // Take the type from the front of the parts
        std::string type = Utility::trim(parts.front());
        parts.erase(parts.begin());

        Vector2f position;
        Vector2f size;

        for (std::string& part : parts)
        {
            std::vector<std::string> property = Utility::split(part, ':');

            property[0] = Utility::trim(property[0]);
            property[1] = Utility::trim(property[1]);

            // Get the first (and hopefully only) character from the property name
            switch (property[0][0])
            {
                case 'x':
                {
                    position.x = std::stof(property[1]);
                    break;
                }
                case 'y':
                {
                    position.y = std::stof(property[1]);
                    break;
                }
                case 'w':
                {
                    size.x = std::stof(property[1]);
                    break;
                }
                case 'h':
                {
                    size.y = std::stof(property[1]);
                    break;
                }
                case 'i':
                {
                    keyId = std::stoi(property[1]);
                    break;
                }
            }
        }

        if (type == "Tile")
        {
            // Create a tile at the position, and with the size gathered above
            std::unique_ptr<Tile> tile = std::make_unique<Tile>(renderer, "TileFloor.bmp", size * tileSize);
            tile->setPosition(position * tileSize);
            // Move the tile to the array
            tiles.insert(tiles.end(), std::move(tile));
        }
        else if (type == "Key")
        {
            // Create a key at the position gathered above
            std::unique_ptr<Key> key = std::make_unique<Key>(keyId, renderer);
            key->setPosition(position * tileSize);
            // Move the key to the array
            keys.insert(keys.end(), std::move(key));
        }
		else if (type == "Door")
		{
			// Create a door at the position gathered above
			std::unique_ptr<Door> door = std::make_unique<Door>(keyId, renderer);
			door->setPosition(position * tileSize);
			// Move the door to the array
			doors.insert(doors.end(), std::move(door));
		}
        else if (type == "PlayerStart")
        {
            playerStart = position * tileSize;
        }
		else if (type == "Enemy")
		{
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(renderer);
			enemy->setPosition(position * tileSize);
			enemies.insert(enemies.end(), std::move(enemy));
		}
		else if (type == "MovingEnemy")
		{
			std::unique_ptr<MovingEnemy> enemy = std::make_unique<MovingEnemy>(renderer);
			enemy->setPosition(position * tileSize);
			enemies.insert(enemies.end(), std::move(enemy));
		}
    }

    file.close();
}

void Level::draw(Vector2f cameraPosition)
{
	for (std::shared_ptr<Tile>& tile : tiles)
	{
		tile->draw(cameraPosition);
	}

    for (std::shared_ptr<Key>& key : keys)
    {
        key->draw(cameraPosition);
    }

	for (std::shared_ptr<Door>& door : doors)
	{
		door->draw(cameraPosition);
	}

	for (std::shared_ptr<Enemy>& enemy : enemies)
	{
		enemy->draw(cameraPosition);
	}
}

Sweep Level::sweepIntersection(AABB& object, Vector2f delta)
{
    Sweep nearest;
    nearest.hit.hit = false;
    nearest.time = 1.f;
    nearest.position = object.getPosition() + delta;

    for (std::shared_ptr<Tile>& tile : tiles)
    {
        Sweep sweep = tile->sweepIntersection(object, delta);

        // If the collision was closer than the last nearest, replace it as the nearest
        if (sweep.time < nearest.time)
        {
            nearest = sweep;
        }
    }

    return nearest;
}

std::vector<int> Level::getKeyIntersections(AABB& object)
{
    std::vector<int> results;

    // If the object is colliding with a key, add it to the array to be returned
	auto iterator = keys.begin();
	while (iterator != keys.end())
	{
		if (iterator->get()->testIntersection(object).hit)
		{
			results.insert(results.end(), iterator->get()->getId());
			iterator = keys.erase(iterator);
		}
		else
		{
			++iterator;
		}
	}

    return results;
}

Sweep Level::sweepDoorIntersection(AABB& object, Vector2f delta)
{
	Sweep result;
	result.hit.hit = false;
	result.time = 1.f;
	result.position = object.getPosition() + delta;

	for (std::shared_ptr<Door>& door : doors)
	{
		Sweep sweep = door->sweepIntersection(object, delta);

		// If the collision was closer than the last nearest, replace it as the nearest
		if (sweep.time < result.time)
		{
			result = sweep;
		}
	}

	return result;
}

Vector2f Level::getPlayerStart()
{
	return playerStart;
}
