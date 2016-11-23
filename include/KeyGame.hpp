#pragma once

#include "Game.hpp"
#include "Player.hpp"
#include "InputManager.hpp"
#include "Level.hpp"

class KeyGame : public Game
{
private:
	Player player;

	Level level;

	InputManager inputManager;

	void update(float deltaTime);
	void draw();
public:
	KeyGame(std::string title, Vector2i size, Uint32 flags);
};
