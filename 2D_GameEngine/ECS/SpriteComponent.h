#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h""
//hold the animation using a std::map
#include <map>
#include "../AssetManager.h"

//class constructor that inherits the values and functions from the Component class in ECS
class SpriteComponent : public Component {
private:
	//pointer to transform component that stores and returns x and y values
	TransformComponent* transform;
	//create a pointer to a texture file used to load object models
	SDL_Texture* texture;
	//create 2 rectangles used to display on the renderer
	SDL_Rect srcRect, destRect;

	//check if the current entity that holds the sprite is animated or not
	//fasle by default
	bool animated = false;
	//the number of frames in the animation (0 by default bc animated is false)
	int frames = 0;
	//speed represents the delay between frames in milliseconds 
	int speed = 100;

public:
	// default to 0 bc if we don't animate the sprite, the initial y position has to be 0
	// the sprite index
	// changes in the update() function
	int animIndex = 0;
	/*
	*	create a map for animations
	*	const char* represents what we are going to name the animation (an id for the animation)
	*	Animations animation for the title / id that represents the animation 
	*/
	std::map<const char*, Animation> animations;

	/*
	*	An enumeration of flags that can be used in the flip parameter for SDL_RenderCopyEx.
	*	SDL_RenderCopyExCopy copies a portion of the texture to the current rendering, with optional rotation and flipping.
	*	Used to determine what to be done on the image
	* 
	*	SDL_FLIP_NONE is the flag for not flipping the image
	*/
	SDL_RendererFlip spriteFlag = SDL_FLIP_NONE;

	//class declaration that uses the compiler generated version of the function
	//if user fails to create a function given proper values, create and use a default one
	SpriteComponent() = default;

	//@params {char} path to the texture we are going to use
	//returns a sprite object that we can render to the screen with a certain texture and the path to the texture
	SpriteComponent(std::string id){
		//setTex(path);
		setTex(id);
	}

	/*
	*	Constructor that takes in a sprite and animates it
	*	@params {char}	path to the texture we are going to use
	*	@params {bool}	represents if the sprite needs to be animated or not
	*	@params {int}	represents how fast the animation is played (increasing speed slows down the delay between frames)
	* 
	*	returns a sprite object that we can render to the screen with a certain texture
	*/

	SpriteComponent(std::string id , bool isAnimated) {
		//the entity is animated
		animated = isAnimated;

		//create default animations
		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 8, 100);

		//add the animations to the std::map
		//only adds it once for the first creation of a sprite
		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");
		//setTex(path);
		setTex(id);
	}

	//eliminate and clear memory
	~SpriteComponent() {
	}

	//load texture to current sprite
	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}
	
	//initialize the sprite component
	void init() override {
		//reference to transform component by taking the reference of what it belongs to
		transform = &entity->getComponent<TransformComponent>();

		//start of the x and y
		srcRect.x = srcRect.y = 0;
		/*
		* width and height of the source rectangle
		* Source rectangle goes from the start of the image (top left / 0,0) 
		* and copies the pixels until it reaches a certain width and height
		* 
		* transform->width/height are the default sizes for the sprites
		*/
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	//update the transform of the x and y to be the current transform
	//used for rendering out the correct positions on the screen
	void update() override {

		if (animated) {
			/*
			*	Tile sheet for animation is done in a way where different animations are placed
			*	on top and beside one another. They are divided by the same # of pixels across and above from each other 
			*	Determine the current frame and multiply the srcRect.x to get to that current frame. 
			*	essentially set the new x position as the new (0,0) to be used to send image to destRect.x
			*	
			*	Get the number of milliseconds since SDL library initialization with sdl_getticks
			*	(SDL_GetTicks() / speed) % frames returns the remainder of what is left
			*	corresponds to what the current frame is at a given time and what sprite should be used
			*/
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		/*
		*	Tile sheets place separate animations above and below each other in the png file
		*	animIndex represents the desired animation and it's position on the tilesheet
		*	every image is divided by the same amount of space / pixels
		*	animIndex * transform->height multiplies the default pixel height distance with the # of indexs to get to correct position
		*	
		*	essentially sets the new y position as the new (0,0) to be used to send images to destRect.x
		*	
		*/
		srcRect.y = animIndex * transform->height;

		/*
		* copies the image from srcRect and then scales it up or down
		* so it will fit into the destRect.
		* destRect subtracts the camera.x and y in order to allow the camera to move as the same speed of the player
		*
		* Use the destRect to push to the screen to display what is needed
		* scale the image and increase w and h by a 'scale' size variable
		* 
		*/
		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	//using the TextureManager class, draw out onto the screen
	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect,spriteFlag);
	}

	/*
	*	Changes the current frames and index that we need
	*	@params {char*} receives the name of the animation that we are looking for from the map
	*	the map will return the actual animation from the animation class
	*	
	*	plays the animation given a certain index / 
	*/
	void Play(const char* animName) {
		//return the number of total frames from a given animation
		frames = animations[animName].frames;
		//return the index / position as to where the animation is located on the tilesheet
		animIndex = animations[animName].index;
		//the delay between frames in milliseconds / speed of the animation 
		speed = animations[animName].speed;
	}
};