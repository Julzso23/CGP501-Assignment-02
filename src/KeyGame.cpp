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

	player.collisionSlide(levelManager, deltaTime);

    // For each key the player may be colliding with, add it to the player's inventory
    for (int keyId : levelManager.getCurrent()->getKeyIntersections(player))
    {
        player.addKey(keyId);
    }

	levelManager.getCurrent()->updateEnemies(levelManager, deltaTime);

    // Centre the camera on the player
	int renderW, renderH;
	SDL_RenderGetLogicalSize(renderer, &renderW, &renderH);
	Vector2f newCameraPosition(player.getPosition().x - renderW / 2.f, player.getPosition().y - renderH / 2.f);
	cameraPosition = Utility::lerp(cameraPosition, newCameraPosition, deltaTime * 3.f);
}

void KeyGame::draw()
{
    levelManager.getCurrent()->draw(cameraPosition);

	player.draw(cameraPosition);
}

KeyGame::KeyGame() :
	player(renderer, "Player.bmp", true),
	levelManager({"level1", "level2"}, renderer)
{
	player.setPosition(levelManager.getCurrent()->getPlayerStart());
	player.setGravity(1000.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
