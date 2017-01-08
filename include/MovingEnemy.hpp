#pragma once

#include "Enemy.hpp"
#include "Player.hpp"

class MovingEnemy : public Enemy, public Player
{
private:
    int direction;
public:
    MovingEnemy(SDL_Renderer* renderer);

    void setMoveDirection(float value, float deltaTime);
    void onCollision(Vector2f normal);
};