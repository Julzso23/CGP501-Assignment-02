#include "Entities/Key.hpp"

Key::Key(int id, SDL_Renderer* renderer) :
    id(id),
    Bitmap(renderer, "Key.bmp", true)
{
}

int Key::getId()
{
    return id;
}
