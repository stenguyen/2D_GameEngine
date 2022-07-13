#pragma once

#include "ECS.h"
//#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	//represents where the tiles actually are in the game world
	Vector2D position;

	//default constructor for individual tiles
	TileComponent() = default;

	//deconstructor
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}
	
	/*
	*	@params {int}	(srcX,srcY) location of the textures to be loaded on the tilesheet
	*	@params {int}	(xpos,ypos) Position on the screen where the texture is loaded
	*	@params {int}	tsize represents the size of the title
	*	@params {int}	tscale represents # to scale up the tile by
	*	@params {char*}	path in where the assets are stored
	*/
	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path) {
		//load the texture given the position where it is at
		texture = TextureManager::LoadTexture(path);
		//keeps track of where a tile actually is, not just where they are being drawn
		//can be used with the vector of tiles to check and see positions
		position.x = xpos;
		position.y = ypos;

		//positions to serach the texture in order to find out where the texture is actually loaded
		srcRect.x = srcX;
		srcRect.y = srcY;
		//size of the image we are displaying / size of image on the tilesheet
		srcRect.w = srcRect.h = tsize;

		//printing x and y position on the screen 
		destRect.x = xpos;
		destRect.y = ypos;
		//size of the image on the screen
		//64 instead of 32 bc we want to double his size
		destRect.w = destRect.h = tsize*tscale;

	}

	// updates the place where the objects are rendered to
	// really no idea wtf is happen
	//think it makes search that the camera is following the palyer or smt
	void update() override {
		//the position where the player should be drawn
		//subtracts the real / inital position of the tile with the camera position
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}


	//override the default drawing method
	void draw() override {
		//use the texture manager draw function and draw out the tile
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}


};