#include "Level.hpp"
#include <fstream>

Level::Level(std::string fileName, SDL_Renderer* renderer) :
	renderer(renderer)
{
	std::ifstream file;
	file.open("resources/levels/" + fileName + ".level");

	Vector2f position;

	char tileType;
	while (file >> std::noskipws >> tileType)
	{
		switch (tileType)
		{
			case 'w':
			{
				std::unique_ptr<Tile> tile = std::make_unique<Tile>(renderer, "TileFloor.bmp");
				tile->setPosition(position);
				tiles.insert(tiles.end(), std::move(tile));
				position.x += 64.f;
				break;
			}
			case ' ':
			{
				position.x += 64.f;
				break;
			}
			case '\n':
			{
				position = Vector2f(0.f, position.y + 64.f);
				break;
			}
			case 'p':
			{
				playerStart = position;
				position.x += 64.f;
				break;
			}
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
}

Sweep Level::sweepIntersection(AABB& object, Vector2f delta)
{
    Sweep nearest;
    nearest.time = 1.f;
    nearest.position = object.getPosition() + delta;

    for (std::shared_ptr<Tile>& tile : tiles)
    {
        // Make a rough check to see if the tile is close enough to be worth testing
        if ((object.getCentre() - tile->getCentre()).length() <= 100.f)
        {
            Sweep sweep = tile->sweepIntersection(object, delta);
            if (sweep.time < nearest.time)
            {
                nearest = sweep;
            }
        }
    }

    return nearest;
}

Vector2f Level::getPlayerStart()
{
	return playerStart;
}
