#pragma once

#include "Vector2.hpp"

struct CollisionResponse
{
	bool overlapping;
	Vector2f reaction;
};
