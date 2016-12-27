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

    Vector2f velocity = player.getVelocity();

    Sweep result = levelManager.getCurrent()->sweepIntersection(player, velocity * deltaTime);

    if (result.time != 1.f)
    {
        float dotProduct = (velocity.x * result.hit.normal.y + velocity.y * result.hit.normal.x) * (1.f - result.time);
        velocity.x = result.hit.normal.y * dotProduct;
        velocity.y = result.hit.normal.x * dotProduct;
    }

    if (result.time == 0.f)
    {
        player.move(result.hit.delta);
        player.onCollision(result.hit.normal);
        result = levelManager.getCurrent()->sweepIntersection(player, velocity * deltaTime);
    }

    player.move(velocity * deltaTime);

    if (result.hit.hit)
    {
        player.onCollision(result.hit.normal);
    }

    for (int keyId : levelManager.getCurrent()->getKeyIntersections(player))
    {
        player.addKey(keyId);
    }

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
	levelManager({"level1"}, renderer)
{
	player.setPosition(levelManager.getCurrent()->getPlayerStart());
	player.setGravity(1000.f);

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
