#include "TextureManager.h"

//sdl_texture pointer that takes in takes in the texture we want to load + the renderer
//@params {char*} link to texture that we want to use (.png, .jpg, etc)
//@params {SDL_Renderer*} renderer we are rendering to (no need anymore, just accessing a static one from game.hpp)
//@returns {sdl_texture} return a pointer to an sdl_texture representing the texture that is to be shown
SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	/*
	*	surfaces are pixels stored in SDL2
	*	textures is image data stored on the GPU
	*	textures are somewhere on video memory and is easier to access and draw
	*/
	//create temp pointer for player that loads a surface
	//tmpSurface is pixel date used to fill the texture
	SDL_Surface* tmpSurface = IMG_Load(texture);
	//variable for the texture of thing
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);


	//return the texture to the user
	return tex;

	//creates a texture from surface (alternative way that can be fixed)
	//playerTex = IMG_LoadTexture(renderer, "assets/player.png");
}

/// Copies a portion of the source texture to the current rendering target
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{	
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
