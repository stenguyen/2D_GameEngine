#pragma once
#include "Components.h"
#include "SDL.h"

//class constructor that inherits the values and functions from the Component class in ECS
class SpriteComponent : public Component {
private:
	//pointer to transform component that stores and returns x and y values
	TransformComponent* transform;
	//create a pointer to a texture file used to load object models
	SDL_Texture* texture;
	//create 2 rectangles used to display on the renderer
	SDL_Rect srcRect, destRect;

public:
	//class declaration that uses the compiler generated version of the function
	//if user fails to create a function given proper values, create and use a default one
	SpriteComponent() = default;

	//@params {char} path to the texture we are going to use
	//returns a sprite object that we can render to the screen with a certain texture
	SpriteComponent(const char* path) {
		setTex(path);
	}

	//load texture to current sprite
	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}
	
	//initialize the sprite component
	void init() override {
		//reference to transform component by taking the reference of what it belongs to
		transform = &entity->getComponent<TransformComponent>();

		//start of the x and y
		srcRect.x = srcRect.y = 0;
		/*
		* width and height of the source rectangle
		* Source rectangle goes from the start of the image (top left / 0,0) 
		* and copies the pixels until it reaches a certain width and height
		*/
		srcRect.w = srcRect.h = 32;
		
		/*
		* copies the image from srcRect and then scales it up or down
		* so it will fit into the destRect.
		* 
		* Use the destRect to push to the screen to display what is needed
		* scale the image and increase w and h by 2
		*/
		destRect.w = destRect.h = 64;
	}

	//update the transform of the x and y to be the current transform
	//used for rendering out the correct positions on the screen
	void update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	//using the TextureManager class, draw out onto the screen
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

};