#include "CollisionObject.hpp"
#include <cmath>

void CollisionObject::setSize(Vector2f size)
{
	this->size = size;
}

Vector2f CollisionObject::getSize()
{
	return size;
}

void CollisionObject::setVelocity(Vector2f velocity)
{
	this->velocity = velocity;
}

Vector2f CollisionObject::getVelocity()
{
	return velocity;
}

bool CollisionObject::isOverlapping(CollisionObject& object)
{
	return (getPosition().x + getSize().x > object.getPosition().x) &&
		(getPosition().x < object.getPosition().x + object.getSize().x) &&
		(getPosition().y + getSize().y > object.getPosition().y) &&
		(getPosition().y < object.getPosition().y + object.getSize().y);
}

CollisionResponse CollisionObject::testCollision(CollisionObject& object)
{
	CollisionResponse response;
	if (!isOverlapping(object))
	{
		response.overlapping = false;
		return response;
	}

	if (getVelocity().x > 0.f)
	{
		response.reaction.x = object.getPosition().x - (getPosition().x + getSize().x);
	}
	else
	{
		response.reaction.x = object.getPosition().x + object.getSize().x - getPosition().x;
	}

	if (getVelocity().y > 0.f)
	{
		response.reaction.y = object.getPosition().y - (getPosition().y + getSize().y);
	}
	else
	{
		response.reaction.y = object.getPosition().y + object.getSize().y - getPosition().y;
	}

	if (abs(response.reaction.x) > abs(response.reaction.y))
	{
		response.reaction.x = 0.f;
	}
	else
	{
		response.reaction.y = 0.f;
	}

	return response;
}
