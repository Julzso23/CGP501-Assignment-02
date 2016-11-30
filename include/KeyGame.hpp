#pragma once

#include "Game.hpp"
#include "Player.hpp"
#include "InputManager.hpp"
#include "LevelManager.hpp"

class KeyGame : public Game
{
private:
	Player player;
	LevelManager levelManager;
	InputManager inputManager;
	Vector2f cameraPosition;

	void update(float deltaTime);
	void draw();
public:
	KeyGame(std::string title, Vector2i size, Uint32 flags);
};
