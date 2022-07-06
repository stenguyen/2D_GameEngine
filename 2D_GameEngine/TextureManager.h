#pragma once
#include "Game.hpp"

//load textures
class TextureManager {

public:
	//load texture given image
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};