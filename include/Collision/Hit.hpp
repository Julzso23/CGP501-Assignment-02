#pragma once

#include "Vector2.hpp"

struct Hit
{
	bool hit;
	Vector2f position;
	Vector2f delta;
	Vector2f normal;
	float time;
};