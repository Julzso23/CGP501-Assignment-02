#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"
#include "LevelManager.hpp"
#include <vector>

class Player : public virtual AABB, public virtual Bitmap
{
private:
	float gravity;
	bool grounded;
    Vector2f velocity;

    std::vector<int> keys;
public:
	Player(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);

	void setGravity(float gravity);
	float getGravity();

	void setMoveDirection(float value, float deltaTime);

	void collisionSlide(LevelManager& levelManager, float deltaTime);

    virtual void onCollision(Vector2f normal);

    Vector2f getVelocity();

	void jump();

    void addKey(int keyId);
    void removeKey(int keyId);
    bool hasKey(int keyId);
};
