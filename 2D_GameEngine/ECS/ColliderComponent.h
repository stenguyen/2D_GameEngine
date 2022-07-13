#pragma once
#include <string>
#include "Components.h"
#include "../TextureManager.h"

//Collider Rectangle that encompasses the entity
//Used in conjunction with collision.cpp
class ColliderComponent : public Component {
public:
	//collider rectangle that is used with the collision detection
	SDL_Rect collider;
	//when you check collision, find out what type of action must happen
	std::string tag;

	//texture to display the collider texture on the map
	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	//pointer to transform component that stores and returns x and y values
	TransformComponent* transform;

	//set the tag of the collider to 't'
	//used for comparing two types of that are interacting (ex: player hits enemy, what do you do)
	ColliderComponent(std::string t) {
		tag = t;
	}

	//constructor for a collider component (called in map.cpp)
	ColliderComponent(std::string t, int xpos, int ypos, int size){
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	//initialize the component
	void init() override {
		//if the entity doesn't have the transform component, add the component to the entity
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		//once we are sure transform component exists, set pointer to the transform component
		transform = &entity->getComponent<TransformComponent>();

		//load the collider texture
		tex = TextureManager::LoadTexture("assets/coltex.png");
		//state the source rectangle and what parts of the image gets put in (all of it)
		srcR = { 0,0,32,32 };
		//create the destination rectangle at position (x,y) given the size of the collider
		destR = { collider.x, collider.y, collider.w, collider.h };

		//add a new element at the end of the vector
		//Game::colliders.push_back(this);
	}

	// adjusts(transforms) the size of the collider hitbox to be same size and position as the entity
	//collider rectangle should overlap and be of equal size to the player character
	void update() override {
		//do this the component that do not have a transform component
		if (tag != "terrain") {
			//position of the rectangle
			//static_cast<int> transforms the float value to an integer one
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			//scale the rectangle / hitbox to be the same size as the object
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}


		//have the camera move the same speed and display it as the player 
		//literally have no idea i have to ask brian
		destR.x = collider.x - Game::camera.x;
		destR.y = collider.y - Game::camera.y;

	}

	//draws the collider onto the screen
	void draw() override {
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}

};