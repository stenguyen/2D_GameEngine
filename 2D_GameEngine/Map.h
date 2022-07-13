#pragma once
//for the path to be able to function
#include <string>

class Map
{
public:
	//constructor
	Map(const char* mfp, int ms, int ts);
	//deconstructor
	~Map();

	//load the map given a path to file that has map details and max width and height 
	void LoadMap(std::string path, int sizeX, int sizeY);
	//add a tile given the position of the tile to render from the tilesheet and the (x,y) where it should be placed
	void AddTile(int srcX, int srcY, int xpos, int ypos);


private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	//represents mapscale*tilesize
	int scaledSize;

};

