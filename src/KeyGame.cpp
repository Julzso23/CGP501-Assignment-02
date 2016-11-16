#include "KeyGame.hpp"

void KeyGame::update(float deltaTime)
{
	inputManager.update();

	if (inputManager.keyDown(SDL_SCANCODE_SPACE))
	{
		player.jump();
	}

	float value = inputManager.getAxis();
	player.move(value * 200.f, deltaTime);

	player.updateCollisions(monster);
}

void KeyGame::draw()
{
	player.draw();
	monster.draw();
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "resources/textures/monster.bmp", true),
	monster(renderer, "resources/textures/TileFloor.bmp", true)
{
	monster.setPosition(Vector2f(0.f, 200.f));
	player.setGravity(300.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
