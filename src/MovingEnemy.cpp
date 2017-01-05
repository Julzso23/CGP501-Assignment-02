#include "MovingEnemy.hpp"
#include "Utility.hpp"

MovingEnemy::MovingEnemy(SDL_Renderer* renderer) :
	direction(1),
	Player(renderer, "SawBlade.bmp", true),
	Bitmap(renderer, "SawBlade.bmp", true),
	Enemy(renderer)
{
}

void MovingEnemy::setMoveDirection(float value, float deltaTime)
{
	setAngle(getAngle() + 45 * deltaTime);

	Player::setMoveDirection(value * direction, deltaTime);
}

void MovingEnemy::onCollision(Vector2f normal)
{
	if (normal.x != 0.f)
	{
		direction = (int)Utility::sign(normal.x);
	}

	Player::onCollision(normal);
}
