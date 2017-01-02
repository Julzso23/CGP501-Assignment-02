#include "Player.hpp"

Player::Player(SDL_Renderer* renderer, std::string path, bool hasTransparency) :
	Bitmap(renderer, path, hasTransparency),
	gravity(0.f),
	grounded(false)
{
    // Set the collision box size to the texture size
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

void Player::onCollision(Vector2f normal)
{
    // If the player is touching the ground
    if (normal == Vector2f(0.f, -1.f))
    {
        grounded = true;
        velocity.y = 0.f;
    }
    // If the player is touching the roof
    else if (normal == Vector2f(0.f, 1.f))
    {
        velocity.y = 0.f;
    }
}

Vector2f Player::getVelocity()
{
    return velocity;
}

void Player::jump()
{
    // The player can only jump if they're on the ground
	if (grounded)
	{
        velocity.y = -500.f;
	}
}

void Player::addKey(int keyId)
{
    keys.insert(keys.end(), keyId);
}

void Player::removeKey(int keyId)
{
    if (hasKey(keyId))
    {
        auto iterator = std::find(keys.begin(), keys.end(), keyId);
        keys.erase(iterator);
    }
}

bool Player::hasKey(int keyId)
{
    auto iterator = std::find(keys.begin(), keys.end(), keyId);
    return iterator != keys.end();
}
