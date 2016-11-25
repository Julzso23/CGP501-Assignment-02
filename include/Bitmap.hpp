#pragma once

#include <SDL.h>
#include <string>
#include "Transformable.hpp"

class Bitmap : public virtual Transformable
{
protected:
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
public:
	Bitmap(SDL_Renderer* renderer, std::string path, bool hasTransparency = false);
	~Bitmap();
	void draw(Vector2f cameraPosition);
};
