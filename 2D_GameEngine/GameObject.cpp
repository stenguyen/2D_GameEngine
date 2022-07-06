#include "GameObject.h"
#include "TextureManager.h"

///	Takes in textures we want to show + the renderer
/// @params {char*} a jpg, png, etc of whatever we want to show on screen
/// @params {sdl_renderer*} the renderer we are rendering the picture to (not needed anymore, 
///							using a global static one from Game.hpp
/// @params {int} x,y are the initial positions to place the texture
GameObject::GameObject(const char* texturesheet, int x, int y) {
	//set texture from header file to be a loaded texture file that can be rendered
	objTexture = TextureManager::LoadTexture(texturesheet);

	//set the initial positions when object is initialized
	xpos = x;
	ypos = y;
}

/// update function that does all movement for a character
/// currently working on only the player character
void GameObject::Update() {
	//increase x and y position every call
	xpos++;
	ypos++;

	//set the width and height of the rectangle
	//currently 32 as that is the size of our player currently (I think)
	srcRect.h = 32;
	srcRect.w = 32;
	//set x and y location of the rectangle's upper left corner
	srcRect.x = 0;
	srcRect.y = 0;

	//set the destination rectangles to be in the same position as the initial ones
	destRect.x = xpos;
	destRect.y = ypos;
	//set the width and height of the destination rectangle
	//adjusts the size of the player on the screen
	//destRect is a rectangle variable that controls the size of the object on the screen
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

/// Rendering code that places the desired object onto the screen
///	can adjust the size of the object that shows on the screen too
/// Copies a portion of the source texture to the current rendering target
/// srcrect is the source to be drawn on the destination/target (dstrect)
/// 
/// @params {SDL_Renderer*} rendering context
/// @params {SDL_Texture*} source texture
/// @params {SDL_Rect*} (srcrect) the source SDL_Rect structure or NULL for the entire texture
/// @params {SDL_Rect*} (dstrect) the destination SDL_Rect structure or NULL for the entire rendering target; 
///						the texture will be stretched to fill the given rectangle
/// 
/// @returns 0 on success or error code on failure
/// 
void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
