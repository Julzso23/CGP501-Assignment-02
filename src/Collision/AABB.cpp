#include "Collision\AABB.hpp"
#include "Utility.hpp"

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

Hit AABB::testIntersection(Vector2f point)
{
	Hit result;
	Vector2f difference = point - getPosition();
	Vector2f collisionPoint = getHalf() - Vector2f(abs(difference.x), abs(difference.y));

	if (collisionPoint.x <= 0.f || collisionPoint.y <= 0.f)
	{
		result.hit = false;
		return result;
	}

	if (collisionPoint.x < collisionPoint.y)
	{
		float signX = Utility::sign(difference.x);
		result.delta.x = collisionPoint.x * signX;
		result.delta.y = 0.f;
		result.normal.x = signX;
		result.normal.y = 0.f;
		result.position.x = getPosition().x + (getHalf().x * signX);
		result.position.y = point.y;

		return result;
	}

	float signY = Utility::sign(difference.y);
	result.delta.x = 0.f;
	result.delta.y = collisionPoint.y * signY;
	result.normal.x = 0.f;
	result.normal.y = signY;
	result.position.x = point.x;
	result.position.y = getPosition().y + (getHalf().y * signY);

	return result;
}
