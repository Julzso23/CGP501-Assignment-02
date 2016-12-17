#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"

class Tile : public AABB, public Bitmap
{
public:
	Tile(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);
};
