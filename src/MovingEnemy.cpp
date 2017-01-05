#include "MovingEnemy.hpp"

MovingEnemy::MovingEnemy(SDL_Renderer* renderer) :
	direction(1),
	Player(renderer, "SawBlade.bmp", true),
	Bitmap(renderer, "SawBlade.bmp", true)
{
}

void MovingEnemy::onCollision(Vector2f normal)
{
	direction = normal.x;
}
