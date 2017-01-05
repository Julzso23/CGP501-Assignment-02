#include "Enemy.hpp"
#include "Level.hpp"

Enemy::Enemy(SDL_Renderer* renderer) :
	Bitmap(renderer, "Spikes.bmp", true)
{
	setSize(Vector2f((float)surface->w, (float)surface->h));
}

void Enemy::playerCollision(std::shared_ptr<Level> level)
{
	level->load();
}
