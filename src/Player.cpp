#include "Player.hpp"

Player::Player(SDL_Renderer* renderer, std::string path, bool hasTransparency) :
	Bitmap(renderer, path, hasTransparency),
	gravity(0.f),
	grounded(false)
{
	setSize(Vector2f((float)surface->w, (float)surface->h));
}

void Player::setGravity(float gravity)
{
	this->gravity = gravity;
}

float Player::getGravity()
{
	return gravity;
}

void Player::setMoveDirection(float value, float deltaTime)
{
	velocity.x = value;
	velocity.y += gravity * deltaTime;

	grounded = false;
}

Vector2f Player::getVelocity()
{
    return velocity;
}

void Player::jump()
{
	if (grounded)
	{
        velocity.y = -500.f;
	}
}
