#pragma once

#include "CollisionObject.hpp"
#include "Bitmap.hpp"

class Tile : public CollisionObject, public Bitmap
{
public:
	Tile(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);
};
