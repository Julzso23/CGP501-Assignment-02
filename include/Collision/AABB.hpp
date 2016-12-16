#pragma once

#include "Transformable.hpp"
#include "Collision\Hit.hpp"
#include "Collision\Segment.hpp"
#include "Collision\Sweep.hpp"

class AABB : public Transformable
{
private:
	Vector2f size;
public:
	AABB();

	Vector2f getSize();
	void setSize(Vector2f size);
	Vector2f getHalf();
	Vector2f getCentre();

	Hit testIntersection(Vector2f point);
	Hit testIntersection(Segment segment, Vector2f padding);
	Hit testIntersection(AABB& other);
	Sweep sweepIntersection(AABB& other, Vector2f delta);
};