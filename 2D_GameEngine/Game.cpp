#include "Game.hpp"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

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
	map = new Map();

	//ecs implementation
	//add position and sprite component to the newPlayer character
	player.addComponent<TransformComponent>(0,0);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();

}

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
	manager.refresh();
	manager.update();

	//gets the position(Vector2D) variable in the transform component 
	//adjust the X and Y by doing operands on it's values
	//player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));


	//if the player has an x greater than 100, swap textures
	//if (player.getComponent<TransformComponent>().position.x > 100) {
	//	player.getComponent<SpriteComponent>().setTex("assets/buster.png");
	//}

	//std::cout << player.getComponent<PositionComponent>().x() << "," <<
	//	player.getComponent<PositionComponent>().y() << std::endl;
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

	//uses Map class to render out image
	map->DrawMap();
	manager.draw();


	//uses GameObject class to render out player
	//player->Render();
	//enemy->Render();



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

