#pragma once
#include "ECS/ECS.h"
#include "AssetManager.h"
#include "Game.hpp"

#include <SDL.h>
//for text
#include <SDL_ttf.h>
#include <string>


class UILabel : public Component
{
public:
	/*
	* @params {xpos, ypos}	position as to where the label is going to be placed
	* @params {text, font}	text and font that represents the text to display and the font used
	* @params {colour}		using an SDL_Color to represent colour for the text
	*/
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		//create the label text that is to be placed on the screen given the variables
		SetLabelText(labelText, labelFont);
	}
	~UILabel()
	{}
	//create the font and text to be shown
	void SetLabelText(std::string text, std::string font)
	{
		/*
		* https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
		* https://pub.dev/documentation/sdl2/latest/sdl2_generated_lib_sdl_ttf/TTF_RenderText_Blended.html
		* @params {TTF_RenderText_Blended}	returns a surface given the font, string, and colour to be shown
		*									use blended for high quality text
		*/
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(labelFont), text.c_str(), textColour);
		//convert the surface to a texture that holds the text
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		//free memory
		SDL_FreeSurface(surf);
		//let us get the width and height of the texture
		// automatically set the textures of the w and h to the variable 'position'
		//https://wiki.libsdl.org/SDL_QueryTexture
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}
	//draw the rectangle
	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	//where to place the text
	SDL_Rect position;
	//represents the text to be written
	std::string labelText;
	//id for the font being used to retrieve from the asset manager
	std::string labelFont;
	//colour of the text
	SDL_Color textColour;
	//holds the text as an SDL_Texture
	SDL_Texture* labelTexture;
};