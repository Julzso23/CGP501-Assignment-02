#include "Bitmap.hpp"
#include <Windows.h>

Bitmap::Bitmap(SDL_Renderer* renderer, std::string path, bool hasTransparency) :
	renderer(renderer)
{
	surface = SDL_LoadBMP(path.c_str());
	if (!surface)
	{
		MessageBox(NULL, SDL_GetError(), ("Loading surface for bitmap: " + path + " failed.").c_str(), MB_ICONERROR | MB_OK);
		return;
	}

	if (hasTransparency)
	{
		Uint32 colourKey = SDL_MapRGB(surface->format, 255, 0, 255);
		SDL_SetColorKey(surface, SDL_TRUE, colourKey);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
	{
		MessageBox(NULL, SDL_GetError(), ("Loading texture for bitmap: " + path + " failed.").c_str(), MB_ICONERROR | MB_OK);
		return;
	}
}

Bitmap::~Bitmap()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	if (surface)
	{
		SDL_FreeSurface(surface);
	}
}

void Bitmap::draw()
{
	if (texture)
	{
		SDL_Rect rect = {(int)floor(getPosition().x), (int)floor(getPosition().y), surface->w, surface->h};
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
}
