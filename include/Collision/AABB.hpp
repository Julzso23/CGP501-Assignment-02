#pragma once

#include "Transformable.hpp"

class AABB : public Transformable
{
private:
	Vector2f size;
public:
	AABB();

	Vector2f getSize();
	Vector2f getHalf();
	Vector2f getCentre();
};