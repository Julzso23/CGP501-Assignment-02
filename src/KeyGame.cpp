#include "KeyGame.hpp"
#include "Utility.hpp"

void KeyGame::update(float deltaTime)
{
	inputManager.update();

	if (inputManager.buttonDown(SDL_SCANCODE_SPACE, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A))
	{
		player.jump();
	}

	float value = inputManager.getAxis();
	player.setMoveDirection(value * 400.f, deltaTime);

    Sweep result = levelManager.sweepIntersection(player, player.getVelocity() * deltaTime);
    player.move(player.getVelocity() * deltaTime * result.time + result.hit.normal);

	int renderW, renderH;
	SDL_RenderGetLogicalSize(renderer, &renderW, &renderH);
	Vector2f newCameraPosition(player.getPosition().x - renderW / 2.f, player.getPosition().y - renderH / 2.f);
	cameraPosition = Utility::lerp(cameraPosition, newCameraPosition, deltaTime * 3.f);
}

void KeyGame::draw()
{
	player.draw(cameraPosition);
	levelManager.draw(cameraPosition);
}

KeyGame::KeyGame() :
	player(renderer, "monster.bmp", true),
	levelManager({"level1", "level2"}, renderer)
{
	player.setPosition(levelManager.getCurrent()->getPlayerStart());
	player.setGravity(1000.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
