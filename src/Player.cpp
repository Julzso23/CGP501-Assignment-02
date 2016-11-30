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

void Player::move(float value, float deltaTime)
{
	Vector2f velocity = getVelocity();
	velocity.x = value;
	velocity.y += gravity * deltaTime;
	setVelocity(velocity);

	Transformable::move(Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));

	grounded = false;
}

void Player::jump()
{
	if (grounded)
	{
		setVelocity(Vector2f(getVelocity().x, -500.f));
	}
}

void Player::updateCollisions(CollisionObject & other)
{
	CollisionResponse response = testCollision(other);
	if (response.overlapping)
	{
		Transformable::move(response.reaction);
		if (abs(response.reaction.y) > 0.f)
		{
			setVelocity(Vector2f(getVelocity().x, 0.f));

			if (response.reaction.y < 0.f)
			{
				grounded = true;
			}
		}
	}
}
