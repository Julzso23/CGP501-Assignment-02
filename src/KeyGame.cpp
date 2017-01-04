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

    // Calculate the first collision sweep
    Sweep result = levelManager.getCurrent()->sweepIntersection(player, velocity * deltaTime);

    // If the player is inside a tile, move them out of it
    if (result.time == 0.f)
    {
        player.move(result.hit.delta);
        player.onCollision(result.hit.normal);
    }

    // Keep doing sweeps until there isn't a collision
    while (result.time != 1.f)
    {
		// Change the player's velocity to slide along the tile
        float dotProduct = (velocity.x * result.hit.normal.y + velocity.y * result.hit.normal.x) * (1.f - result.time);
        velocity.x = result.hit.normal.y * dotProduct;

        if (result.hit.normal.y != 0.f)
        {
            velocity.y *= result.time;
        }
        
        // Trigger the player's collision event
        player.onCollision(result.hit.normal);

        // Do another sweep
        result = levelManager.getCurrent()->sweepIntersection(player, velocity * deltaTime);
    }

	result = levelManager.getCurrent()->sweepDoorIntersection(player, velocity * deltaTime);

	// Keep doing sweeps until there isn't a collision
	while (result.time != 1.f)
	{
		// Change the player's velocity to slide along the door
		float dotProduct = (velocity.x * result.hit.normal.y + velocity.y * result.hit.normal.x) * (1.f - result.time);
		velocity.x = result.hit.normal.y * dotProduct;

		if (result.hit.normal.y != 0.f)
		{
			velocity.y *= result.time;
		}

		// Trigger the player's collision event
		player.onCollision(result.hit.normal);

		if (player.hasKey(((Door*)result.hit.object)->getId()))
		{
			player.removeKey(((Door*)result.hit.object)->getId());
			levelManager.nextLevel();
			player.setPosition(levelManager.getCurrent()->getPlayerStart());
		}

		// Do another sweep
		result = levelManager.getCurrent()->sweepDoorIntersection(player, velocity * deltaTime);
	}

    // Actually move the player in the world
    player.move(velocity * deltaTime);

    // For each key the player may be colliding with, add it to the player's inventory
    for (int keyId : levelManager.getCurrent()->getKeyIntersections(player))
    {
        player.addKey(keyId);
    }

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
