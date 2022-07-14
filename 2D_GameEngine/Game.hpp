#pragma once

//include sdl libraries and standard input output
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

//forward declaration of the AssetManager class
class AssetManager;
//forward declaration of the ColliderComponent class
class ColliderComponent;



class Game
{
public:
	//constructor and deconstructor
	Game();
	~Game();

	//initialize game states
	void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
	//event handler
	void handleEvents();
	//goes through the game objects and updates it all (all the events)
	void update();
	//allow main to know that game is still running
	bool running() { return isRunning; };
	//render out the game to the screen
	void render();
	//memory management 
	void clean();


	//create a static renderer to be accessed throughout the whole program
	static SDL_Renderer* renderer;
	//create a static event that is to be accessed throughout the whole program (can't be accidentally changed)
	static SDL_Event event;

	//create a vector (a dynamic list) of collider pointers that deals with how an oject collides with another
	//static std::vector<ColliderComponent*> colliders
	//check to see if the game is running
	static bool isRunning;
	//camera object that views the player
	//has width and height (for how much of the screen can be viewed
	static SDL_Rect camera;

	//Asset manager pointer to use in game.cpp
	static AssetManager* assets;

	//map labels that corresponds to certain groups in the ECS.h group vector
	//each label represents a number and increases on the next one
	//this allows for them to be added to a table easily
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};



private:
	int cnt; //counter variable
	SDL_Window* window;
};
