#pragma once

#include "Collision\Hit.hpp"

struct Sweep
{
    Hit hit;
    Vector2f position;
    float time;
};