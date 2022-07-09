#pragma once
#include "Components.h"
#include "../Vector2D.h"

// class constructor that inherits the values and functions from the Component class in ECS
// could use struct instead of class, but lazy (default struct: public, default class: private)
// https://cplusplus.com/forum/beginner/235722/#:~:text=The%20single%20colon%20could%20also,class%20behind%20the%20single%20colon.
class TransformComponent : public Component {
public:
	//positions of the component using Vector2D
	//stores the x and y values as Vector2D variable
	Vector2D position;

	//how fast the entity is moving
	Vector2D velocity;
	int speed = 3;

	//default constructor that is called without parameters
	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}
	//default constructor
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}


	//override the inherited update() command and do this instead
	//move the player a certain amount 
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

	}
};