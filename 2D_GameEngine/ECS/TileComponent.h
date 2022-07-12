#pragma once

#include "ECS.h"
//#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	//default constructor for individual tiles
	TileComponent() = default;

	//deconstructor
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	
	/*
	*	@params {int}	(srcX,srcY) location of the textures to be loaded on the tilesheet
	*	@params {int}	(xpos,ypos) Position on the screen where the texture is loaded
	*	@params {char*}	path in where the assets are stored
	*/
	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {
		//load the texture given the position where it is at
		texture = TextureManager::LoadTexture(path);
		//positions to serach the texture in order to find out where the texture is actually loaded
		srcRect.x = srcX;
		srcRect.y = srcY;
		//size of the image we are displaying / size of image on the tilesheet
		srcRect.w = srcRect.h = 32;

		//printing x and y position on the screen 
		destRect.x = xpos;
		destRect.y = ypos;
		//size of the image on the screen
		//64 instead of 32 bc we want to double his size
		destRect.w = destRect.h = 64;

	}
	
	//override the default drawing method
	void draw() override {
		//use the texture manager draw function and draw out the tile
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

};