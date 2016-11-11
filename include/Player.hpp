#pragma once

#include "CollisionObject.hpp"
#include "Bitmap.hpp"

class Player : public CollisionObject, public Bitmap
{
public:
	Player(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);
};
