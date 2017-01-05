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

void Player::collisionSlide(LevelManager& levelManager, float deltaTime)
{
	Vector2f velocity = getVelocity();

	// Calculate the first collision sweep
	Sweep result = levelManager.getCurrent()->sweepIntersection(*this, velocity * deltaTime);

	// If the player is inside a tile, move them out of it
	if (result.time == 0.f)
	{
		move(result.hit.delta);
		onCollision(result.hit.normal);
	}

	// Keep doing sweeps until there isn't a collision
	while (result.time != 1.f)
	{
		// Change the player's velocity to slide along the tile
		float dotProduct = (velocity.x * result.hit.normal.y + velocity.y * result.hit.normal.x) * (1.f - result.time);
		velocity.x = result.hit.normal.y * dotProduct;

		if (result.hit.normal.y != 0.f)
		{
			velocity.y *= result.time;
		}

		// Trigger the player's collision event
		onCollision(result.hit.normal);

		// Do another sweep
		result = levelManager.getCurrent()->sweepIntersection(*this, velocity * deltaTime);
	}

	result = levelManager.getCurrent()->sweepDoorIntersection(*this, velocity * deltaTime);

	// Keep doing sweeps until there isn't a collision
	while (result.time != 1.f)
	{
		// Change the player's velocity to slide along the door
		float dotProduct = (velocity.x * result.hit.normal.y + velocity.y * result.hit.normal.x) * (1.f - result.time);
		velocity.x = result.hit.normal.y * dotProduct;

		if (result.hit.normal.y != 0.f)
		{
			velocity.y *= result.time;
		}

		// Trigger the player's collision event
		onCollision(result.hit.normal);

		if (hasKey(((Door*)result.hit.object)->getId()))
		{
			removeKey(((Door*)result.hit.object)->getId());
			levelManager.nextLevel();
			setPosition(levelManager.getCurrent()->getPlayerStart());
		}

		// Do another sweep
		result = levelManager.getCurrent()->sweepDoorIntersection(*this, velocity * deltaTime);
	}

	// Actually move the player in the world
	move(velocity * deltaTime);
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
