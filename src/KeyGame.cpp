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

	levelManager.updateCollisions(player);

	int windowW, windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);
	Vector2f newCameraPosition(player.getPosition().x - windowW / 2.f, player.getPosition().y - windowH / 2.f);
	cameraPosition = Vector2f::lerp(cameraPosition, newCameraPosition, deltaTime * 3.f);
}

void KeyGame::draw()
{
	player.draw(cameraPosition);
	levelManager.draw(cameraPosition);
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "monster.bmp", true),
	levelManager(player, {"level2.txt"}, renderer)
{
	player.setGravity(400.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
