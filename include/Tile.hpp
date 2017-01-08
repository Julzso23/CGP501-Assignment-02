#pragma once

#include "Collision/AABB.hpp"
#include "Bitmap.hpp"

class Tile : public AABB
{
private:
    Bitmap bitmap;
public:
    Tile(SDL_Renderer* renderer, std::string path, Vector2f size);
    void draw(Vector2f cameraPosition);
};
