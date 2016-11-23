#include "KeyGame.hpp"

void KeyGame::update(float deltaTime)
{
	inputManager.update();

	if (inputManager.buttonDown(SDL_SCANCODE_SPACE, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
	{
		player.jump();
	}

	float value = inputManager.getAxis();
	player.move(value * 200.f, deltaTime);

	level.updateCollisions(player);
}

void KeyGame::draw()
{
	player.draw();
	level.draw();
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "monster.bmp", true),
	level("level1.txt", renderer)
{
	player.setPosition(Vector2f(64.f, 64.f));
	player.setGravity(300.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
