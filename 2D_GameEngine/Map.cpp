#include "Map.h"
//for reading file input
#include <fstream>
#include "Game.hpp"



Map::Map() {
	
}

//deconstructor
Map::~Map() {

}

//load the map given a path to file that has map details
//sizeX and sizeY is the max size
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	
	//corresponds to data of a certain tile at position (x,y)
	//each tile corresponds to a different int which corresponds to a separate sprite
	//ex: 0 = grass, 1 = water, etc
	char tile;
	//set variable that corresponds to file we're loading
	std::fstream mapFile;
	//open file
	mapFile.open(path);

	//loop through the input stream and assign values to tile
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			//extracts characters from the stream as unformatted input
			//assigns the unformatted char into char tile
			mapFile.get(tile);

			/*
			* create a tile component given it's id and position
			* use atoi to convert from char to int
			* 
			* multiply x and y by 32 bc each tile is 32 pixels big
			*/
			Game::AddTile(atoi(&tile), (x * 32), (y * 32));
			//ignores the next character in the stream
			//ignores the commas between the numbers
			mapFile.ignore();
		}
	}


	//close the file
	mapFile.close();
}
