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
//the "attributes" that they have
class Component;
//the object / thing that holds multiple attributes together
class Entity;
//manager class that holds all the entities
class Manager;



//type alias declaration 
//for each component (positions, physics, input handling, etc), we need ID representing it
//size_t is an unsigned int where it can store the maximum size of a theoretically possible array of any type
//using brings all of ComponentID members into the current scope (ex: using namespace std;)
//using brings one specific ComponentID member to the current scope (ex: using ComponentID = std::size_t;)
//
//std::size_t is the type of ANY(can be char, short ,int, long, etc) sizeof expression and as is guaranteed to be able to 
//express the maximum size of any object (including any array) in C++
//
//essentially make a large int with each int corresponding to a different component 
//https://stackoverflow.com/questions/2532542/what-does-using-mean-in-c

/*
* typedef for the componentID type
* 
*/
using ComponentID = std::size_t;
/*
* typdef for the Group ID which corresponds 
* to the type that they are (enemy, ally, wall, etc)
* used for colliders and what happens when touch
* groups / layers that can be used for render layers and collision layers
*/
using Group = std::size_t;


/// inline function copies the code from the function definition directly into the code of the calling function
/// rather than creating a separate set of instructions in memory, it just uses the pure function itself.
/// increase by one after every call
inline ComponentID getComponentID() {
	// every time we call this function, lastID will remember what it was (bc it is static, every update will stay keep the value it has rn) 
	static ComponentID lastID = 0;
	// returns the next ID // the next uniqueID
	return lastID++;
}

/*
*	template to create a function that returns a unique ComponentID based upon the type passed (T) using the getComponentID() function
*	noexcept is used for exiting a function because an throw is impossible / doesn't matter (noexceptions)
*	use noexcept keyword with those lines of code that does not cause an exception, and if they cause we can ignore it.
* 
*	Every time we call this function with a specific type 'T', we are calling an instantiation of this template with a unique static 'typeID' variable
*	When we call this function for the first with a specific Type 'T1' "TypeID" will be initialized with a unique ID
*	Subsequent calls with the same type 'T1' will return the same ID
*
*/
template <typename T> inline ComponentID getComponentTypeID() noexcept {
	// We can use a 'static_assert' to make sure this function is only 
	// called with types that inherit from 'Component'
	static_assert (std::is_base_of<Component, T>::value, "T must inherit from Component");
	// create a static variable that corresponds to it's ID
	static ComponentID typeID = getComponentID();
	// return it's ID to the user
	return typeID;
}

// (constexpr):constant expression indicates that the value, or return value, is constant and, where possible, is computed at compile time.
// a constexpr integral value can be used wherever a const integer is required, such as in template arguments and array declarations.
// maxComponents represents the maximum # of components that an entity holds
constexpr std::size_t maxComponents = 32;
//32 groups / layers that can be used for render layers and collision layers
constexpr std::size_t maxGroups = 32;


// stores 32 bits of either 0 or 1, true or false, etc (32 is from the maxComponents variable)
// used compare whether or not an entity has a certain component or not
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

// creates an array of only component pointers with a max size of maxComponents
// array of all component pointers which points to all the components that an entity has
using ComponentArray = std::array<Component*, maxComponents>;

// component class which corresponds to an attribute that an entity has
class Component {
public:
	// has reference to it's owner 
	// entity corresponds to an entity object which has multiple components
	Entity* entity = nullptr;

	// virtual is polymorphism (allows the user to change and override the current code)
	// will be called after a component is added to an entity
	virtual void init() {};

	virtual void update() {};
	virtual void draw() {};

	// deconstructor for component object
	virtual ~Component() {}
};


/*
*	Container for the components
*	has functions that can add/update/draw the components individually
*/

class Entity {
private:
	// if false, remove from game
	// is dead or not essentially
	bool active = true;

	// vectors are similar to a dynamic array bc they automatically change size (creates a list of components)
	// unique_ptr points to an object that will be reclaimed when that pointer is destroyed and used again (smart pointer)
	// used when you want multiple pointers to the same resource
	// https://stackoverflow.com/questions/16894400/how-to-declare-stdunique-ptr-and-what-is-the-use-of-it
	// vector of component pointers with variable name of components, to allow polymorphism
	std::vector<std::unique_ptr<Component>> components;

	/*
	*	Array to quickly get a component with a specific ID and a bitset to check
	*	the existence of a component with a specific ID
	* 
	*/
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	// runs the update function all components
	void update() {
		//loop through all the components and run the components.update()
		//https://stackoverflow.com/questions/58116510/in-for-auto-c-str-what-exactly-is-c
		/*
		*	c is a local variable whose scope is for the entire for block
		*	auto& will automatically deduce what type was inputted and adjust what type they use
		*	ex: if components was a string, it will deduce char
		* 
		*	components corresponds to the vector set in the private section of the entity class
		*	runs the component.update() function on the current component (their own special one) 
		*	run through each component in the vector and do the function
		*/ 
		for (auto& c : components) c->update();

	}

	// runs the draw function for all components to draw on the screen
	void draw() { 
		/*
		*	c is a local variable whose scope is for the entire for block
		*	auto& will automatically deduce what type was inputted and adjust what type they use
		*	ex: if components was a string, it will deduce char
		*
		*	components corresponds to the vector set in the private section of the entity class
		*	runs the component.draw() function for the current component (their own special one in their header file) 
		*	run through each component in the vector and do the function
		*/
		for (auto& c : components) c->draw();
	}

	// returns boolean to see if the calling entity is still in use
	// const bc the answer will never change
	bool isActive() const { return active; }

	// call to make sure the entity is not in use
	// can be called on any given component bc any given component has a reference to their main entity
	void destroy() { active = false; }

	// template check to see if given entity has a given component
	//to check if this entity has a component, query the bitset
	template <typename T> bool hasComponent() const {
		//check to see if entity has a component by comparing its total bit string to the identifier of the one being looked for
		//Check position of the bitSet to see if true or false given the index where the componentID should be located
		//true if found, false otherwise
		return componentBitSet[getComponentTypeID<T>()];
	}
	

	/*
	*	https://www.youtube.com/watch?v=QAmtgvwHInM
	*	Using variadic templates and emplacement, construct components and add to entity
	* 
	*	@params {T} is the component type (string, int, etc)
	*	@params {TArgs} is a parameter pack of types used to construct the component
	*			typename...TArgs allows for an arbitrary number of arguments
	* 
	*	@params {T&} A reference to an object of type T
	*				 T& addComponent(....) is a function that returns pointer reference to the component
	* 
	* 	uses forward referencing to forward the arguments from the template (TArgs&&... mArgs)
	*	to another function as they are (lvalue as lvalue, rvalue as rvalue)
	*	
	*/
	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		//ensure it doesn't exist
		//assert(!hasComponent<T>());

		//allocate memory for component of type 'T' on the heap by forwarding all the arguments 
		//from above into the constructor of the component itself
		//place the new allocated component into the variable c
		T* c(new T(std::forward<TArgs>(mArgs)...));

		//set the parent entity of the constructor to the current entity
		//set the component's entity(parent) to the current instance / calling entity
		c->entity = this;
		
		/*
		*	wrap the raw pointer c into a smart pointer of type<Component> named uPtr
		*	A smart pointer is a class that wraps a ‘raw’ (or ‘bare’) C++ pointer, to manage the lifetime of the object being pointed to.
		*   A smart pointer by comparison defines a policy as to when the object is destroyed.
		* 
		*	used so we can emplace the pointer to the end of the vector of components in the parent class of entity + memory leaks
		*/
		std::unique_ptr<Component> uPtr{ c };
		/*
		*	used so we can emplace the pointer to the end of the vector of components in the parent class of entity
		*	emplace_back inserts a new element at the end of the vector, after the current last element
		*	
		*	https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used
		*	'std::move" is used to indicate that an object t may be "moved from"
		*	'std::move' changes an expression from being an lvalue (such as a named variable) to being an xvalue.
		*	an xvalue (an “eXpiring” value) is a glvalue that denotes an object whose resources can be reused and used 
		*	elsewhere since it is going to be destroyed soon anyway
		* 
		*	'std::move' is required, as 'std::unique_ptr' cannot be copied
		*	
		* 
		*/
		components.emplace_back(std::move(uPtr));


		/*
		*	getComponentTypeID<T>() is the index of the array
		*	when we add a component of type 'T', we add it to the bitset and array
		*	add the component to the components the entity can use
		*	set it so the component is always in the same spot in the array
		*/
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		//initializing function from Component class
		//calls 'Component::init()'
		c->init();

		/* return a reference to the newly added component */
		return *c;
	}




	/*
	*	To retrieve a specific component, we get it from the array
	*   Template of type T that returns pointer to this component of type T
	*	can be used like gameObject.getComponent<PositionComponent>().setXpos(25); or smt
	* 
	* 
	*	template<typename T> 
	*		T& getComponent() const {} also works

	*
	*/
	template<typename T> T& getComponent() const {
		//assert(hasComponent<T>());

		//retrieve the pointer from the array with the index of it's position
		auto ptr(componentArray[getComponentTypeID<T>()]);
		//return the pointer in a way that lets us do smt to the component
		//casting the pointer to the type of 'T' because we are sure that the pointer is pointing to the right type
		return *static_cast<T*>(ptr);
	}


};

/*
*	Container for the entities
*	has functions that can add/update/draw the entities individually
*	similar to format of Entitiy class
*/
class Manager {
private:
	//vector that stores smart pointers of entities
	std::vector<std::unique_ptr<Entity>> entities;
public:
	//update each entity
	void update() {
		//loop through all the components and run their respective components.update()
		for (auto& e : entities) e->update();
	}
	//draw to the screen all entities
	void draw() {
		for (auto& e : entities) e->draw();
	}

	//function that cleans up and removes all the "dead" entities
	void refresh() {
		//removes an element / elements from a vector in the range of all entities
		//remove only if the entity is not active
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	//add new entity to world
	//returns a pointer to the entity
	Entity& addEntity() {
		// create new entity
		Entity* e = new Entity();
		// add the entitiy to the end of the vector of all entities
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		//return pointer to the new entity
		return *e;
	}

};


