#pragma once
//Entity Component System
//for input and output 
#include <iostream>
//arrays that can change in size
//same as dynamic arrays with the ability to resize itself automatically
#include <vector>
//for dynamic memory management (allocation and deallocation, etc)
#include <memory>
//functions for variety of things (searching, sorting, counting, manipulating, etc)
#include <algorithm>
//stores elements with only two values (0 or 1, true or false, etc)
//used for the entity control
#include <bitset>
//include the fixed sized array
#include <array>

//classes for the ECS to function
class Component;
class Entity;

//for each component (positions, physics, input handling, etc), we need ID representing it
//size_t is an unsigned int where it can store the maximum size of a theoretically possible array of any type
//using brings all of ComponentID members into the current scope (ex: using namespace std;)
//using brings one specific ComponentID member to the current scope (ex: using ComponentID = std::size_t;)
//
//std::size_t is the type of any sizeof expression and as is guaranteed to be able to 
//express the maximum size of any object (including any array) in C++
/*https://stackoverflow.com/questions/2532542/what-does-using-mean-in-c*/
using ComponentID = std::size_t;


/// inline function copies the code from the function definition directly into the code of the calling function
/// rather than creating a separate set of instructions in memory, it just uses the pure function itself.
inline ComponentID getComponentID() {
	//every time we call this function, lastID will remember what it was (bc it is static, every update will stay keep the value it has rn) 
	static ComponentID lastID = 0;
	//returns the next ID
	return lastID++;
}

//create a template function where it returns the componentID by using the getComponentID() function
//function that is able to be used for more than one certain type
//noexcept is used for exiting a function because an throw is impossbile / unacceptable (noexceptions)
//https://stackoverflow.com/questions/33210169/how-to-use-noexcept-in-c-or-how-does-it-work
template <typename T> inline ComponentID getComponentID() noexcept {
	//create a static function/variable that corresponds to it's ID (idk)
	static ComponentID typeID = getComponentID();
	//return it's ID to the user
	return typeID();
}

//(constexpr):constant expression indicates that the value, or return value, is constant and, where possible, is computed at compile time.
//constexpr integral value can be used wherever a const integer is required, such as in template arguments and array declarations.
//maxComponents represents the maximum # of components that an entity holds
constexpr std::size_t maxComponents = 32;

//stores 32 bits of either 0 or 1, true or false, etc (32 is from the maxComponents variable)
using ComponentBitSet = std::bitset<maxComponents>;

//takes in a pointer to a component and the # of max components
//function which compares current entity and sees if it has a certain component or not
using ComponentArray = std::array<Component*, maxComponents>;

//component class which corresponds to an attribute that an entity has
class Component {
public:
	//has reference to it's owner
	Entity* entity;
	//virtual is polymorphism
	//allows the user to change and override the current code
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	//deconstructor for component
	virtual ~Component() {}
};

class Entity {
private:
	//if false, remove from game
	bool active = true;
	//vector similar to a dynamic array that automatically changes size (creates a list of components)
	//unique_ptr points to an object that will be reclaimed when that pointer is destroyed
	//used when you want multiple pointers to the same resource
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update() {
		for (auto& c : components) c->update();
	}

};


