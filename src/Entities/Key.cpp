#include "Entities/Key.hpp"

Key::Key(int id, SDL_Renderer* renderer) :
    id(id),
    Bitmap(renderer, "Key.bmp", true)
{
	setSize(Vector2f((float)surface->w, (float)surface->h));
}

int Key::getId()
{
    return id;
}
