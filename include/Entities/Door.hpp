#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"

class Door : public AABB, public Bitmap
{
private:
    int id;
public:
    Door(int id, SDL_Renderer* renderer);

    int getId();
};