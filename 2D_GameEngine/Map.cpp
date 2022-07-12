#include "Map.h"
//for reading file input
#include <fstream>
#include "Game.hpp"



Map::Map() {
	
}

//deconstructor
Map::~Map() {

}

//load the map given a path to file that has map details (the 2d array)
//sizeX and sizeY is the max size
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	
	//corresponds to data of a certain tile at position (x,y)
	//each tile corresponds to a different int which corresponds to a separate sprite
	//ex: 0 = grass, 1 = water, etc
	//char tile;
	
	//string that holds what tile is at a given position on the map
	char c;

	//set variable that corresponds to file we're loading
	std::fstream mapFile;
	//open file
	mapFile.open(path);

	//the image that the tile uses and its coordinates on the tile sheet
	int srcX, srcY;

	/*
	* create a tile component given it's id and position
	* use atoi to convert from char to int
	* loop through the input stream and assign values to tile
	*
	* 
	* multiply x and y by 32 bc each tile is 32 pixels big
	*/

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			//extracts characters from the stream as unformatted input
			//assigns the unformatted char into char tile

			//get the x and y of the source value from the map
			/*
			*	This is the when the id is greater than 9
			*	Before when we had char tile, and mapFile.get(tile), it would only get the first value of the map file
			*	and then ignore the comma as it was only one digit. With two digits, we look at the first digit (y) to 
			*	see the which row the current tile is on and then look at the next digit to see the coloumn.
			*	we use get(c) and atoi(&c) to get the position then convert to an int
			* 
			*	ex: 25 = 2nd row, 5th column
			* 
			*	Using these values, we can find out where on the tilesheet the image is 
			*	for this tile by mulitplying the x and y by 32 (each image is 32x32 pixels)
			* 
			*/
			mapFile.get(c);
			srcY = atoi(&c) * 32;
			mapFile.get(c);
			srcX = atoi(&c) * 32;


			//Game::AddTile(atoi(&tile), (x * 32), (y * 32));
			//add the tiles given which tile image is being used on the tilesheet
			//and the position of where the tile will be printed on the screen
			//doubling the size of the tiles by increase the size from 32 pixels to 64
			Game::AddTile(srcX, srcY, (x * 64), (y * 64));
			//ignores the next character in the stream
			//ignores the commas between the numbers
			mapFile.ignore();
		}
	}


	//close the file
	mapFile.close();
}
