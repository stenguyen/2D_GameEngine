#pragma once

//to store the list of textures that our game has
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
//for manager class
#include "ECS/ECS.h"
//for text and fonts
#include "SDL_ttf.h"

class AssetManager{
public:

	//constructor that takes in a pointer to the manager from ECS.h
	AssetManager(Manager* man);
	//deconstructor
	~AssetManager();

	//game objects

	/*
	*	@params {pos}	position of the entity (x,y)
	*	@params {vel}	velocity of the projectile entity
	*	@params {range}	max distance of the entity before it dies
	*	@params {speed}	speed of the entity / how many pixels it moves per frame
	*	@params {id}	id that corresponds to the current entity for collision and assets manager
	* 
	*	@returns	returns an projectile entity on the screen
	*/
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);


	//texture management
	/*
	*	@params {string}	corresponds to an id that represents which element we are using
	*	@params {char*}		path represents the texture we want to add
	*/
	void AddTexture(std::string id, const char* path);
	//retrieve a texture from the map list
	SDL_Texture* GetTexture(std::string id);
	//add a font type to be used in the game with it's size (path is the location where the font is stored
	void AddFont(std::string id, std::string path, int fontSize);
	//retrieve a font from the user
	TTF_Font* GetFont(std::string id);


private:

	//pointer to the manager class
	Manager* manager;
	//the string represents a 'key' that corresponds to a pointer to and SDL_Texture which would be the actual value
	//essentially a giant list with the index being the keys
	std::map<std::string, SDL_Texture*> textures;
	//create a map of fonts
	std::map < std::string, TTF_Font*> fonts;
};