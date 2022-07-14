#include "Map.h"
//for reading file input
#include <fstream>
#include "Game.hpp"
#include "ECS/ECS.h"
#include "ECS/Components.h"


/*
*	extern keyword tells the compiler that a variable is defined in another source module (outside of the current scope)
*	allows other classes to use the source file for the certain class in other parts of the program
*	
*	include preprocessor directive simply copy/pastes the text of the included file into the 
*	current position in the current file. extern marks that a variable or function exists externally to this source file.
*/
extern Manager manager;

/*
*	@params {char*} represents the map file path to load and get the map (const char* mfp) (not anymore
*	@params {tId}	represents an index to the asset manager that corresponds to an asset
*	@params {int}	ms represents the map scale that will increase or decrease the size of the map
*	@params {int}	ts represents the size of the idividual tiles
* 
*	@returns	constucts a map class with components that lead to less magic numbers and loads the maps
*/
Map::Map(std::string tID, int ms, int ts) {
	//: texID(tID), mapScale(ms), tileSize(ts)
	texID = tID;
	mapScale = ms;
	tileSize = ts;
	scaledSize = ms * ts;
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
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;


			//Game::AddTile(atoi(&tile), (x * 32), (y * 32));
			//add the tiles given which tile image is being used on the tilesheet
			//and the position of where the tile will be printed on the screen
			//doubling the size of the tiles by increase the size from 32 pixels to 64
			AddTile(srcX, srcY, (x * (tileSize*mapScale)), (y * (tileSize * mapScale)));
			//ignores the next character in the stream
			//ignores the commas between the numbers
			mapFile.ignore();
		}
	}
	
	//ignores the space between the differnet map layers
	//ignores the new line
	mapFile.ignore();

	//loop through the next layer to print out the colliders
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			//get the character at the position
			mapFile.get(c);
			//if the character is 1 (representing the collider)
			if (c == '1') {
				//automatically create an entity for the tile collider
				//the entity is stored in the manager class
				auto& tcol(manager.addEntity());
				//add a collider component with the id of "terrain" at position (x,y) with scale size
				tcol.addComponent<ColliderComponent>("terrain", x*scaledSize, y * scaledSize, scaledSize);
				//add the entity to a group named 'groupedColliders'
				tcol.addGroup(Game::groupColliders);
			}
			//ignore the comma right after the character
			mapFile.ignore();
		}
	}

	//close the file
	mapFile.close();
}

// add a title given it's position on the tilemap and and the position where it is printed on the screen
void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	//create a tile entity
	auto& tile(manager.addEntity());
	//add tile component given position, size, and id type
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
	//add the tile to the groupMap (enum definition in game.hpp)
	tile.addGroup(Game::groupMap);
}