#pragma once

#include "CollisionObject.hpp"
#include "Bitmap.hpp"

class Player : public CollisionObject, public Bitmap
{
private:
	float gravity;
	bool grounded;
public:
	Player(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);

	void setGravity(float gravity);
	float getGravity();

	void move(float value, float deltaTime);

	void jump();

	void updateCollisions(CollisionObject& other);
};
