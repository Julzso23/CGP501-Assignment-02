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

	int windowW, windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);
	Vector2f newCameraPosition(player.getPosition().x - windowW / 2.f, player.getPosition().y - windowH / 2.f);
	cameraPosition = Vector2f::lerp(cameraPosition, newCameraPosition, deltaTime * 3.f);
}

void KeyGame::draw()
{
	player.draw(cameraPosition);
	level.draw(cameraPosition);
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "monster.bmp", true),
	level("level1.txt", renderer)
{
	player.setPosition(level.getPlayerStart());
	player.setGravity(400.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
