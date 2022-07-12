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
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{	
	/*
	*	Copy a portion of the texture to the current rendering, with optional rotation and flipping.
	*	Instead of using sdl_rendercopy, we use sdl_rendercopyex as ex has more features
	* 
	*	@params {sdl_texture*}	the source texture
	*	@params {sd_rect}		the source SDL_Rect structure or NULL for the entire texture
	*	@params {sdl_rect} 		the destination SDL_Rect structure or NULL for the entire rendering target
	*	the two missing one represents angle and center
	*	@params {double}		an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction
	*	@params {SDL_Point}		a pointer to a point indicating the point around which dstrect will be rotated
	*							(if NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2)(the center)
	*	@params {sdl_flip}		a SDL_RendererFlip value stating which flipping actions should be performed on the texture
	* 

	*/
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
