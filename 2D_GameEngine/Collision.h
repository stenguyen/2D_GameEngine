#pragma once
#include <SDL.h>

//needs to know about this class
class ColliderComponent;

class Collision
{
public:
	//Axis-aligned bounding boxes collision detection given two rectangles
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	//collision detection given two collider components (rectangles with names)
	static bool	AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};

