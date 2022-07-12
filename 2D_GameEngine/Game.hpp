#pragma once

//include sdl libraries and standard input output
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

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

	//add a tile given the position of the tile to render from the tilesheet and the (x,y) where it should be placed
	static void AddTile(int srcX, int srcY, int xpos, int ypos);
	//create a static renderer to be accessed throughout the whole program
	static SDL_Renderer* renderer;
	//create a static event that is to be accessed throughout the whole program (can't be accidentally changed)
	static SDL_Event event;
	//create a vector (a dynamic list) of collider pointers that deals with how an oject collides with another
	static std::vector<ColliderComponent*> colliders;




private:
	int cnt; //counter variable
	bool isRunning;
	SDL_Window* window;
};
