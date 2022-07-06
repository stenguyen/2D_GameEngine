//include header files
#include "Game.hpp"

//game instance pointer
Game *game = nullptr;


int main(int argc, char* argv[]) {

	//set max fps and time between frames
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	//game time / how long the game has been running
	Uint32 frameStart;
	int frameTime;

	//declare new game
	game = new Game();
	//initialize game
	game->init("stweveEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	//game loop
	while (game->running()) {
		//number of milliseconds since SDL library initalization
		frameStart = SDL_GetTicks();

		//-> is the same as . but is used for pointers
		//(*game).handleUpdates(); same as this
		game->handleEvents();
		game->update();
		game->render();

		//number of seconds it took to go through all event, updating renderer, and rendering
		frameTime = SDL_GetTicks() - frameStart;
		//delay frames to ensure consistency / 60fps max
		if (frameDelay > frameTime) {
			//wait a speicified # of miliseconds before returning
			SDL_Delay(frameDelay - frameTime);
		}

	}

	//clean game when exited
	game->clean();

	return 0;
}