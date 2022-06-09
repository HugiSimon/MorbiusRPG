#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
Game* game = nullptr;

int main(int argc, char** argv) {
	game = new Game();
	game->init("Morbius",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,640,false);
	
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
	
}