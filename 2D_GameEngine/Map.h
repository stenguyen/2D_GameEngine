#pragma once
//for the path to be able to function
#include <string>

class Map
{
public:
	//constructor
	Map();
	//deconstructor
	~Map();

	//load the map given a path to file that has map details and max width and height 
	static void LoadMap(std::string path, int sizeX, int sizeY);



private:



};

