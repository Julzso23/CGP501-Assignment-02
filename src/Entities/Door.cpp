#include "Entities/Door.hpp"

Door::Door(int id, SDL_Renderer * renderer) :
    id(id),
    Bitmap(renderer, "Door.bmp", true)
{
    setSize(Vector2f((float)surface->w, (float)surface->h));
}

int Door::getId()
{
    return id;
}
