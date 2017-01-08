#include "Transformable.hpp"

void Transformable::setPosition(Vector2f position)
{
    this->position = position;
}

Vector2f Transformable::getPosition()
{
    return position;
}

void Transformable::move(Vector2f offset)
{
    position += offset;
}
