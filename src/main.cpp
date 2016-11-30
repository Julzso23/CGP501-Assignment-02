#include "KeyGame.hpp"

int main(int argumentCount, char** arguments)
{
	KeyGame game("Key Game", Vector2i(1280, 720), SDL_WINDOW_FULLSCREEN_DESKTOP);
	game.run();

	return 0;
}
