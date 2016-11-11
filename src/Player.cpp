#include "Player.hpp"

Player::Player(SDL_Renderer* renderer, std::string path, bool hasTransparency) :
	Bitmap(renderer, path, hasTransparency)
{
	setSize(Vector2f(surface->w, surface->h));
}