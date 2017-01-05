#pragma once

#include "Collision\AABB.hpp"
#include "Bitmap.hpp"
#include <memory>

class Level;

class Enemy : public virtual AABB, public virtual Bitmap
{
public:
	Enemy(SDL_Renderer* renderer);
	virtual void playerCollision(std::shared_ptr<Level> level);
};