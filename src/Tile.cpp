#include "Tile.hpp"

Tile::Tile(SDL_Renderer* renderer, std::string path, Vector2f size) :
    bitmap(renderer, path, false)
{
    setSize(size);
}

void Tile::draw(Vector2f cameraPosition)
{
    float tileSize = bitmap.getSize().x;
    Vector2f position;

    // Tile the texture across the width and height of the tile object
    for (position.x = getPosition().x;
         position.x < getPosition().x + floor(getSize().x / tileSize) * tileSize;
         position.x += tileSize)
    {
        for (position.y = getPosition().y;
             position.y < getPosition().y + floor(getSize().y / tileSize) * tileSize;
             position.y += tileSize)
        {
            bitmap.setPosition(position);
            bitmap.draw(cameraPosition);
        }
    }
}