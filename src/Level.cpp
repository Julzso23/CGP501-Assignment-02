#include "Level.hpp"
#include <fstream>

Level::Level(std::string fileName, SDL_Renderer* renderer) :
	renderer(renderer)
{
	std::ifstream file;
	file.open("resources/levels/" + fileName);

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
		}
	}

	file.close();
}

void Level::draw()
{
	for (std::shared_ptr<Tile>& tile : tiles)
	{
		tile->draw();
	}
}

void Level::updateCollisions(Player & player)
{
	for (std::shared_ptr<Tile>& tile : tiles)
	{
		player.updateCollisions(*tile.get());
	}
}
