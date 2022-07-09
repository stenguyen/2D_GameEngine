#pragma once
#include "Game.hpp"
#include "ECS.h"
#include "Components.h"


// class constructor that inherits the values and functions from the Component class in ECS
//for the keyboard input from the user
class KeyboardController : public Component {
public:
	//pointer to a transform component to adjust x and y
	TransformComponent* transform;

	//initialize the keyboard controller
	void init() override {
		//set the pointer to be the transform component of the calling entity
		transform = &entity->getComponent<TransformComponent>();
	}
	//access the static event in the game class to adjust for input
	void update() override {
		//if the 
		if (Game::event.type == SDL_KEYDOWN) {
			//key.keysym.syms is used for checking for certain key presses
			//SDLK_# represents a certain key on the keyboard
			switch (Game::event.key.keysym.sym)
			{
			/*
			*	when the w key is pressed, adjust the velocity so it becomes (velocity.y * speed), where speed is the
			*	number of pixels moved and velocity is direction
			* 
			*	-1 will shift the values left / up (as the start of pixel is (0,0) and increases down and right)
			*	+1 will shift the values right / down
			*/
			case SDLK_w:
				transform->velocity.y = -1;
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;

			default:
				break;
			}
		}

		//if the key is not being pressed anymore
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			//assign each velocity back to 0
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;

			default:
				break;
			}
		}
	}
};