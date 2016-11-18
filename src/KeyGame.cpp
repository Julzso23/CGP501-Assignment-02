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

	player.updateCollisions(monster);
}

void KeyGame::draw()
{
	player.draw();
	monster.draw();
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "monster.bmp", true),
	monster(renderer, "TileFloor.bmp", false)
{
	monster.setPosition(Vector2f(0.f, 200.f));
	player.setGravity(300.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
