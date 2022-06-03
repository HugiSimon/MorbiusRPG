#include "Start.h"

Start::Start()
{
}

int Start::startAll()
{
	if (startSDL() == -1) {
		return -1;
	}
	if (startSDLImage() == -1) {
		return -1;
	}
	if (startSDLTTF() == -1) {
		return -1;
	}
	return 0;
}

int Start::startSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}
}

int Start::startSDLImage()
{
	if (IMG_Init(IMG_INIT_JPG) == 0) {
		fprintf(stdout, "Echec de l'initialisation de la SDL Image JPG (%s)\n", IMG_GetError());
		return -1;
	}
	//Mettre tout les autres Modules
}

int Start::startSDLTTF()
{
	if (TTF_Init() == -1) {
		fprintf(stdout, "Echec de l'initialisation de la SDL Ttf (%s)\n", TTF_GetError());
		return -1;
	}
}

SDL_Window* Start::createWindow(const char *name, int n_w, int n_h)
{
	SDL_Window* temp = NULL;
	temp = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, n_w, n_h, SDL_WINDOW_SHOWN);
	return temp;
}

SDL_Renderer* Start::createRenderer(SDL_Window* window, int index)
{
	SDL_Renderer* temp;
	temp = SDL_CreateRenderer(window, index, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return temp;
}

int Start::testAll(SDL_Window* window, SDL_Renderer* renderer)
{
	if (testWindow(window) == -1 || testRenderer(renderer) == -1) {
		return -1;
	}
	return 0;
}

int Start::testWindow(SDL_Window* window)
{
	if (window == NULL) {
		fprintf(stdout, "Erreur de création de la fenêtre (%s)\n", SDL_GetError());
		return -1;
	}
	return 0;
}

int Start::testRenderer(SDL_Renderer* renderer)
{
	if (renderer == NULL) {
		printf("Erreur lors de la creation d'un renderer (%s)", SDL_GetError());
		return -1;
	}
	return 0;
}

int Start::End()
{
	SDL_Event tempEvent;
	if (SDL_PollEvent(&tempEvent)) {
		if (tempEvent.type == SDL_QUIT) {
			return -1;
		}
	}
	return 0;
}
