//include texture manager and the map class
//texture manager used for texture loading
#include "Map.h"
#include "TextureManager.h"

//this is only something temporary 
//plan is to eventually load map from external file
//first level
int lvl1[20][25] = {
	{0,0,0,0,1,1,1,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map() {
	//use the texture manager to load 
	//each number corresponds to a different asset
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");

	//load a map given a design
	LoadMap(lvl1);

	//set the x and y of the source rectangle to be 0
	src.x = src.y = 0;

	//set the source and the destination to be the same size
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	//initialize the destination rectangle on the screen so it's not random
	dest.x = dest.y = 0;
}

//assign the current map level to the real map
//@params {2D arr} the level we design
void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			//set the map in the header file to be this size
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap() {
	//figure out which texture is to be shown
	int type = 0;
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			//set tile type to the value in the index of the array
			type = map[row][column];
			//when the loop iterates, move across by x # of pixels (32 pixels right if column increases by 1)
			dest.x = column * 32;
			dest.y = row * 32;


			switch (type) {
				case 0: // water
					TextureManager::Draw(water, src, dest);
					break;
				case 1: // grass
					TextureManager::Draw(grass, src, dest);
					break;
				case 2: // dirt
					TextureManager::Draw(dirt, src, dest);
					break;
				default:
					break;
			}

		}
	}
}