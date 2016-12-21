#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"

class Key : public AABB, public Bitmap
{
private:
    int id;
public:
    Key(int id, SDL_Renderer* renderer);

    int getId();
};