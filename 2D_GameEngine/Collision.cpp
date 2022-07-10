#include "Collision.h"
//idk why i didn't put this in the header but whatever
#include "ECS/ColliderComponent.h"

/*
*
* Uses Axis-aligned bounding boxes to check if two rectangles are colliding with each other
* If all the checks are true, then the rectangles are colliding
*
*/
bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		) {
		return true;
	}
	return false;
}
bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
	//check if the two collider rectangles are intersecting / colliding (if true, do this)
	if(AABB(colA.collider, colB.collider)) {
		std::cout << colA.tag << "hit: " << colB.tag << std::endl;
		return true;
	}
	else {
		return false;
	}
}