#include "Collision\AABB.hpp"

AABB::AABB() :
	size(0.f, 0.f)
{
}

Vector2f AABB::getSize()
{
	return size;
}

Vector2f AABB::getHalf()
{
	return size / 2.f;
}

Vector2f AABB::getCentre()
{
	return getPosition() + getHalf();
}
