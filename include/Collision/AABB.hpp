#pragma once

#include "Transformable.hpp"
#include "Collision\Hit.hpp"
#include "Collision\Segment.hpp"

class AABB : public Transformable
{
private:
	Vector2f size;
public:
	AABB();

	Vector2f getSize();
	Vector2f getHalf();
	Vector2f getCentre();

	Hit testIntersection(Vector2f point);
	Hit testIntersection(Segment segment, Vector2f padding);
};