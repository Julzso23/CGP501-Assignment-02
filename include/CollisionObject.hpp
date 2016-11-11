#pragma once

#include "Transformable.hpp"
#include "CollisionResponse.hpp"

class CollisionObject : public virtual Transformable
{
private:
	Vector2f size;
	Vector2f velocity;
public:
	void setSize(Vector2f size);
	Vector2f getSize();

	void setVelocity(Vector2f velocity);
	Vector2f getVelocity();

	bool isOverlapping(CollisionObject& object);
	CollisionResponse testCollision(CollisionObject& object);
};
