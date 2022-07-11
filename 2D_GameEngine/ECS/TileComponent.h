#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	//component for the (x,y) position and how to change it
	TransformComponent* transform;
	//component for the image of the entity
	SpriteComponent* sprite;
	
	//corresponds to a rectangle for a tile
	SDL_Rect tileRect;
	//id which determines the sprite and behaviour
	int tileID;
	//string pointer which corresponds to sprite assets
	const char* path;

	//default constructor for individual tiles
	TileComponent() = default;
	
	/*
	*	@params {int} (x,y) positions and width and height
	*	@params {int} id, which corresponds to an identifier with a different texture
	*/
	TileComponent(int x, int y, int w, int h, int id){

		//assign the (x,y), (w,h) values
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		//assign identifier
		tileID = id;

		//initialize the correct sprite depending on the tileID
		switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/water.png";
		default:
			break;
		}
	}

	//initialize the tile Component
	void init() override {
		//create a transform component with the values given through the constructor
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		//set the transform pointer in TileComponent class to point to newly initialized component
		transform = &entity->getComponent<TransformComponent>();

		//add a sprite component to the entity with the pointer to the image we generated in the statement
		entity->addComponent<SpriteComponent>(path);
		//set the sprite pointer in the TitleComponent class to point to a newly initialized sprite component
		sprite = &entity->getComponent<SpriteComponent>();
	}
};