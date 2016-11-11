#include "KeyGame.hpp"

void KeyGame::update(float deltaTime)
{
	float value = inputManager.getAxis();
	player.move(Vector2f(value * 200.f * deltaTime, 0.f));

	player.setVelocity(Vector2f(value, 0.f));

	CollisionResponse response = player.testCollision(monster);
	if (response.overlapping)
	{
		player.move(response.reaction);
	}
}

void KeyGame::draw()
{
	player.draw();
	monster.draw();
}

KeyGame::KeyGame(std::string title, Vector2i size, Uint32 flags) :
	Game(title, size, flags),
	player(renderer, "resources/monster.bmp", true),
	monster(renderer, "resources/monster.bmp", true)
{
	monster.setPosition(Vector2f(200.f, 0.f));

	inputManager.setInputs(SDL_SCANCODE_A, SDL_SCANCODE_D);
}
