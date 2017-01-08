#pragma once

#include "Vector2.hpp"

class Transformable
{
private:
    Vector2f position;
public:
    void setPosition(Vector2f position);
    Vector2f getPosition();
    void move(Vector2f offset);
};
