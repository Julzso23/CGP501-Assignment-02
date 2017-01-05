#include "Enemy.hpp"
#include "Level.hpp"

Enemy::Enemy() :
	Bitmap(renderer, "Spikes.bmp", true)
{
	setSize(Vector2f(surface->w, surface->h));
}

void Enemy::playerCollision(std::shared_ptr<Level> level)
{
	level->load();
}
