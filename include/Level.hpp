#pragma once

#include "Transformable.hpp"
#include "Tile.hpp"
#include <vector>
#include <memory>

class Level : public Transformable
{
private:
	std::vector<std::shared_ptr<Tile>> tiles;
public:
	Level(std::string fileName);
};
