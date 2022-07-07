#pragma once

//include sdl libraries and standard input output
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

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


private:
	int cnt; //counter variable
	bool isRunning;
	SDL_Window* window;
};