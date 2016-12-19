#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"

class Player : public AABB, public Bitmap
{
private:
	float gravity;
	bool grounded;
    Vector2f velocity;
public:
	Player(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);

	void setGravity(float gravity);
	float getGravity();

	void setMoveDirection(float value, float deltaTime);

    void onCollision(Vector2f normal);

    Vector2f getVelocity();

	void jump();
};
