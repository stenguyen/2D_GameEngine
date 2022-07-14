#pragma once
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Vector2D.h"

//class that inherents from a public component
class ProjectileComponent : public Component
{
public:
	/*
	* @params	{rng}	int for range
	* @params	{sp}	int for speed
	* @params	{vel}	vector 2D which corresponds to the velocity
	* 
	* @returns	returns an individual projectile with a certain max range, speed, and velocity
	*/
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel){}
	~ProjectileComponent()
	{}
	//create the initial projectile
	void init() override
	{
		//get the transform component from the calling entity
		transform = &entity->getComponent<TransformComponent>();
		//assign the projectile's velocity to the one of the calling entity
		transform->velocity = velocity;
		//std::cout << transform->position << std::endl;
	}

	//update the projectile after each update call
	void update() override
	{
		//increase the total distance by the constant speed each frame
		//speed denotes how far it moves each frame
		distance += speed;

		//if past the max distance, destroy the entity
		if (distance > range)
		{
			std::cout << "Out of Range" << std::endl;
			entity->destroy();
		}
		/*
		*	Check boundaries if it is in the range
		* 
		*	transform->position.x > Game::camera.x + Game::camera.w:	Current entity is farther than the right hand side of the screen
		*	transform->position.x < Game::camera.x						Current entity is outside the left hand side of the screen
		*	transform->position.y > Game::camera.y + Game::camera.h		If entity is greater than the top of the screen
		*	transform->position.y < Game::camera.y						If entity is less than / below the screen
		* 
		*	@returns delete the entity because it is out of bounds
		* 
		*/
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y)
		{
			std::cout << "Out of bounds!" << std::endl;
			entity->destroy();
		}
	}

private:
	//pointer to the transform component to figure out the (x,y) and size of the component
	//essentially use the transform component to create a an entity and adjust it's position and size
	TransformComponent* transform;

	//default variables
	int range = 0;
	int speed = 0;
	//how far the projectile has gone
	int distance = 0;
	Vector2D velocity;
};