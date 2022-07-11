#include "ECS.h"

//add and entity to a group type named mGroup
void Entity::addGroup(Group mGroup)
{
	//bitset places the group in a certain position and ensures that we can check to see if it is in the group or not
	//by using bitwise comparisons
	groupBitSet[mGroup] = true;
	//use the entity access to the manager class and add the calling entity to a certain group named mGroup
	//this refers to the pointer that points to the calling entity
	manager.AddToGroup(this, mGroup);
}