#pragma once

#include "Game.hpp"
#include "Player.hpp"
#include "InputManager.hpp"

class KeyGame : public Game
{
private:
	Player player;
	Player monster;

	InputManager inputManager;

	void update(float deltaTime);
	void draw();
public:
	KeyGame(std::string title, Vector2i size, Uint32 flags);
};
