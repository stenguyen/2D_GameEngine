#pragma once
#include "Game.hpp"

//the new renderer that will render the game
//renders out outside of the main function
class GameObject{

public:
	//constructor and destructor
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	//function that updates the players on screen
	void Update();
	//render out the screen
	void Render();

private:
	//x and y positions for destRect 
	//should initialize to 0 or smt but nah
	int xpos;
	int ypos;

	//pointer to player texture
	SDL_Texture* objTexture;
	//create a source rectangle and destination rectangle
	//used to place a source on the destination renderer
	SDL_Rect srcRect, destRect;
};

