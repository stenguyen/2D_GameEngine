#pragma once
#include <string>
#include "Components.h"

//Collider Rectangle that encompasses the entity
//Used in conjunction with collision.cpp
class ColliderComponent : public Component {
public:
	//collider rectangle that is used with the collision detection
	SDL_Rect collider;
	//when you check collision, find out what type of action must happen
	//for later
	std::string tag;

	//pointer to transform component that stores and returns x and y values
	TransformComponent* transform;

	//set the tag of the collider to 't'
	//used for comparing two types of that are interacting (ex: player hits enemy, what do you do)
	ColliderComponent(std::string t) {
		tag = t;
	}

	//initialize the component
	void init() override {
		//if the entity doesn't have the transform component, add the component to the entity
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		//once we are sure transform component exists, set pointer to the transform component
		transform = &entity->getComponent<TransformComponent>();

		//add a new element at the end of the vector
		Game::colliders.push_back(this);
	}

	// adjusts(transforms) the size of the collider hitbox to be same size and position as the entity
	//collider rectangle should overlap and be of equal size to the player character
	void update() override {
		//position of the rectangle
		//static_cast<int> transforms the float value to an integer one
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);

		//scale the rectangle / hitbox to be the same size as the object
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}

};