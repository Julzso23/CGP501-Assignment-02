#include "Tile.hpp"

Tile::Tile(SDL_Renderer* renderer, std::string path, bool hasTransparency) :
	Bitmap(renderer, path, hasTransparency)
{
	setSize(Vector2f((float)surface->w, (float)surface->h));
}
