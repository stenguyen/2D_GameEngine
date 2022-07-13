#include "Game.hpp"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

//might not have to include this bc it is in transformComponent.h which is in Components.h
//keep in cuz whatever
#include "Vector2D.h"


//variable for the map object
Map* map;
//variable that is used for entity manager
Manager manager;

//set the renderer in the header file to be null
SDL_Renderer* Game::renderer = nullptr;
//create event handler that handles different type of events with name 'event'
//events are inputs information on current things in the game (mouse input, controller, etc)
//read events from event queue or place events on event queue
SDL_Event Game::event;

//camera rectangle that has initial position of 0,0 and the max width and height of the screen
SDL_Rect Game::camera = { 0,0,800,640};

//pointer to a list of collider pointers
//std::vector<ColliderComponent*> Game::colliders;

//bool to check if the game is running or not
//checks if out of the main menu, etc
bool Game::isRunning = false;




//Create a player entity
auto& player(manager.addEntity());








//constructor and destructor
Game::Game(){}
Game::~Game(){}

/*
	Initialize the initial game window and rendering

	@param {char *} the title of the window given a string
	@param {int} x position of the window on the screen
	@param {int} y position of the window on the screen
	@param {int} width of the window, in screen coordinates
	@param {int} height of the window, in screen coordinates
	@param {Uint32} identifier that represents the window states (fullscreen, borderless, etc)	

	@returns nothing
*/
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){

	//initialized flag if full screen is not selected
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//successful initialization
	/*
		Initialize the SDL library with all subsystems available
		@param {Uint32} flag that represents the subsystems being used (audio, input, timer, event subsystems)
		@returns 0 on success or negative error on error
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!..." << std::endl;

		//using the 'window' variable from header file, create a pointer to a SDL_Window that can be edited
		//@params the initial params given above
		//returns a pointer to the window that was just created or NULL on failure
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		/*
			create a SDL_Renderer pointer named 'renderer' that contains a rendering state for the 'window' variable
			@param {SDL_Window} window pointer where rendering is being displayed
			@param {int} index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
			@param {Uint32} flags that represent the multiple rendering states

			@returns returns a pointer to valid rendering context or NULL if error
		*/
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			//set entire window to be white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else { //if something cannot initialize, game is not running
		isRunning = false;
	}

	//create a player object with a picture texture and the renderer
	//give the initial position of the player
	//player = new GameObject("assets/player.png", 0, 0);
	//enemy = new GameObject("assets/buster.png", 50, 50);

	//create a map object that has a certain level
	map = new Map("assets/terrain_ss.png", 3, 32);

	//ecs implementation

	//load a map given a 2D array, as well as the max col and rows
	map->LoadMap("assets/map.map", 25, 20);

	//add player character with a sprite, (x,y), and the size and scale of the character
	player.addComponent<TransformComponent>(800, 640, 32, 32, 4);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	//add a collider component with a tag of 'player'
	player.addComponent<ColliderComponent>("player");
	//add the player to the groupPlayers label
	player.addGroup(groupPlayers);

	//collision
	//create a wall that starts at (300,300) with a width of 20 and height of 300. scale of 1
	//tutorial using height first, then width
	//wall.addComponent<TransformComponent>(300.0f, 300.0f, 20, 300, 1);
	//wall.addComponent<SpriteComponent>("assets/dirt.png");
	//add a collider component with a tag of 'wall'
	//wall.addComponent<ColliderComponent>("wall");
	//add the wall to the groupMap label
	//wall.addGroup(groupMap);
}

//set all the tiles in the called group to be in the list with name 'tiles'
auto& tiles(manager.getGroup(Game::groupMap));
//set all the players in the called group to be in the list with name 'players'
auto& players(manager.getGroup(Game::groupPlayers));
//set all the colliders in the called group to be in the list with name 'groupColliders'
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::handleEvents(){



	/*
		pass reference to 'event' variable to poll current pending events
		polling an event is getting the current state of the object and checking the contents of event buffer

		@params {SDL_Event} event variable
		@returns 1 if there is a pending event, 0 if none
	*/
	SDL_PollEvent(&event);

	//switch to perform a task given an event type
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false; // if even is quit, then shut off the loop
			break;

		default:
			break;
	}
}

void Game::update(){
	//runs the update command from the GameObject class
	//-> is another way of saying (*player).updater()
	//player->Update();
	//enemy->Update();

	//rectangle corresponding to the player collider at the given call
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	//corresponds to the (x,y) of the player at the given call
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	//delete dead entities
	manager.refresh();

	//go through the entity list in the ECS.h file and update each entity in a loop
	//updating each entity will call upon each entities components
	//each entity has a different update() and refresh component with different attributes
	manager.update();

	//loop through all the colliders to check if player has collided with a collider
	for (auto& c : colliders) {
		//variable that holds a collider to be compared
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		//look for collision with AABB
		if (Collision::AABB(cCol, playerCol)) {
			//if the player did collide, set the player back to where they were before they collided
			//go back in time and retrieve the players old (x,y) state
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	//center the camera on the player
	//camera.x = player.getComponent<TransformComponent>().position.x - (int)((32 * player.getComponent<TransformComponent>().scale) / 2);
	//camera.y = player.getComponent<TransformComponent>().position.y - (int)((32 * player.getComponent<TransformComponent>().scale) / 2);

	//create a rectangle that centers itself aroudn the player
	//the camera is half the size of the window screen and acts as a buffer between the window edge and the player
	//if bounding camera box touches the edge, stop the camera from moving and bind it to the edge until the player moves away
	//can probably make an easier varaible to determine half the size of the width and height
	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//if the camera is moving to the left pass the map, stop the camera
	if (camera.x < 0) {
		camera.x = 0;
	}
	//if the camera is moving up pass the map, stop the camera
	if (camera.y < 0) {
		camera.y = 0;
	}
	//if the camera is moving to the right pass the map, stop the camera
	//camera.w is just the last position of the map / wdith of the map
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	//if the camera is moving down up pass the map, stop the camera
	//camera.h is just the last position of the map / height of the map
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}


	// retrieve the player velocity and player speed
	//used to control how fast the camera moves while following the player
	//Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	//int pSpeed = player.getComponent<TransformComponent>().speed;

	//for (auto t : tiles) {
		/*
		*	move the tiles the inverse of the direction that the player is moving
		*	tiles move the same speed as the player
		* 
		*	ex: if the player is moving up, move the map downwards to fake that the player is actually moving himself upwards
		*	shit is really memory and resource intensive... gotta fix
		* 
		*/
	//	t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
	//	t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	//}

	//takes the collider rectangle of the player entity and the wall entity and uses AABB collision to deal with collision
	//uses a loop that will check all the colliders and does whatever is in the loop
	//for (auto cc : colliders) {
		//check the current collider and return true if collision is true
		//*cc is dereferencing the pointer as colliders is a vector of collider pointers
	//	Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
		/*
			if (Collision::AABB(player.getComponent<ColliderComponent>(), cc*)) {


				//scales the player down, which automatically changes the collider component to also scale down
				player.getComponent<TransformComponent>().scale = 1;
				//bounces the player the same speed back where they came from (opposite)
				//bounce back for an entire frame / next update
				player.getComponent<TransformComponent>().velocity * -1;

				std::cout << "Wall Hit!" << std::endl;
			}
		*/

	//}



	//if the player has an x greater than 100, swap textures
	//if (player.getComponent<TransformComponent>().position.x > 100) {
	//	player.getComponent<SpriteComponent>().setTex("assets/buster.png");
	//}


	//use this if you have multiple levels
	// map->LoadMap();
}



void Game::render(){
	/*
		clears the entire rendering target
		@params {SDL_Renderer*} pointer to sdl_varaiable variable
		@returns 0 on success, error on failure
	*/
	SDL_RenderClear(renderer);

	//this is where we would add stuff to render (bottom then top)
	//manager.draw();


	//uses GameObject class to render out player 
	//player->Render();
	//enemy->Render();

	//for all the tiles in the list 'tiles', draw them out
	for (auto& t : tiles){
		t->draw();
	}
	//for all the colliders in the list 'colliders', draw them out
	for (auto& c : colliders) {
		c->draw();
	}
	//for all the players in the list 'players',draw them out
	for (auto& p : players){
		p->draw();
	}


	/*
		Update the screen with any rendering performed since the previous call.
		Uses Backbuffer to draw everything behind the scenes first before it is put on the screen
		Parse and do all actions in the backbuffer before you display the frame

		@param{SDL_Renderer*} pointer to the renderer
	*/
	SDL_RenderPresent(renderer);
}

void Game::clean(){
	//destroy window and deallocates memory
	SDL_DestroyWindow(window);
	//destroy renderer and deallocates memory
	SDL_DestroyRenderer(renderer);
	//clean up all initialized subsystems
	SDL_Quit();

	std::cout << "Game Cleaned!" << std::endl;
}