#pragma once
//Entity Component System
//for input and output 
#include <iostream>
//arrays that can change in size
//same as dynamic arrays with the ability to resize itself automatically
#include <vector>
//for dynamic memory management (allocation and delocation, etc)
#include <memory>
//funtions for variety of things (searching, sorting, counting, manipulating, etc)
#include <algorithm>
//stores elements with only two values (0 or 1, true or false, etc)
#include <bitset>
//include the fixed sized array
#include <array>


//forward statement
class Component;
class Entity;

//for each component (positions, physics, input handling, etc), we need ID
//create componentID of size_t
//lifts ComponentID into current scope
using ComponentID = std::size_t;


/// inline function copies the code from the function definition directly into the code of the calling function 
/// rather than creating a separate set of instructions in memory.
inline ComponentID getComponentID() {
	//everytime we call this function, lastID will remember what it was (bc static) 
	static ComponentID lastID = 0;
	//returns the next ID
	return lastID++;
}

//create a template function where it returns the componentID by using the getFomponentID() funtion
//noexcept is used for exiting a function because an throw is impossbile / unacceptable
//no idea honestly
template <typename T> inline ComponentID getComponentID() noexcept {
	static Component
}


class ECS
{


};

