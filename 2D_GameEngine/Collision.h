#pragma once
#include <SDL.h>

class Collision
{
public:
	//Axis-aligned bounding boxes collision detection given two rectangles
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);

};

