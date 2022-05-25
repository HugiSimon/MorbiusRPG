#include <stdio.h>
#include <SDL.h>


int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}

	SDL_Window* pWindow = NULL;
	SDL_Renderer* renderer;

	pWindow = SDL_CreateWindow("MorbiusRPG", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

	if (pWindow) {

		if (renderer == NULL)
		{
			printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
			return -1;
		}





		SDL_Delay(3000); //Juste pour le test 


		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(pWindow);

	}
	else {
		fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Quit();
	return 0;

}