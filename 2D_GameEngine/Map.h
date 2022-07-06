#pragma once
#include "Game.hpp"

class Map
{
public:
	//constructor
	Map();
	//deconstructor
	~Map();

	//arr corresponds to map level in 2d array
	void LoadMap(int arr[20][25]);
	void DrawMap();



private:

	//holds the source and destination for rendering
	SDL_Rect src, dest;

	//textures for the titles
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	//rows, cols
	//2D integer array that holds the positions for the map
	//map is size [20x25]
	int map[20][25];





};

