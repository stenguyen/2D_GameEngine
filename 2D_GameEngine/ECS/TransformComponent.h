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

	//initial height and width 
	int height = 32;
	int width = 32;
	int scale = 1;

	//default constructor that is called without parameters
	TransformComponent() {
		position.Zero();
	}
	//constructor that takes in a beginning x and y value
	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	//constructor that takes in default values and only adjusts the scale itself
	TransformComponent(int sc) {
		//rougly the center of the screen
		position.x = 400;
		position.y = 320;
		scale = sc;
	}

	//constructor that takes in the (x,y), initial size, and the scale
	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}


	//override the inherited update() command and do this instead
	//move the player a certain speed*velocity across the map
	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};