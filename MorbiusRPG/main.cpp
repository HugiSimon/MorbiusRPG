#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <random>


int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}

	if (IMG_Init(IMG_INIT_JPG) == 0) {
		fprintf(stdout, "Echec de l'initialisation de la SDL Image (%s)\n", IMG_GetError());
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

	int n_avaX = 0;
	int n_avaY = 0;

	if (pWindow) {

		if (renderer == NULL)
		{
			printf("Erreur lors de la creation d'un renderer (%s)", SDL_GetError());
			return -1;
		}

		SDL_Surface* image = IMG_Load("mdr.jpg");
		if (image == NULL) {
			fprintf(stdout, "Erreur chargement de l'image (%s)", IMG_GetError());
			return -1;
		}

		SDL_Texture* limage = SDL_CreateTextureFromSurface(renderer, image);
		if (limage == NULL) {
			fprintf(stdout, "Erreur chargement de la texture (%s)", SDL_GetError());
			return -1;
		}
		SDL_Rect posRec = { 200, 0, 150, 235 };

		while (true) {
			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					break;
				}

				if (SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_UP :
							n_avaY = -2;
							break;
						case SDLK_DOWN :
							n_avaY = 2;
							break;
						case SDLK_LEFT :
							n_avaX = -2;
							break;
						case SDLK_RIGHT :
							n_avaX = 2;
							break;
						default :
							break;
					}
				}

				switch (event.key.state) {
					case SDL_RELEASED:
						n_avaX = 0;
						n_avaY = 0;
						break;
					default:
						break;
				}
			}

			posRec.x = posRec.x + n_avaX;
			posRec.y = posRec.y + n_avaY;

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, limage, NULL, &posRec);
			SDL_RenderPresent(renderer);

			SDL_Delay(16);
		}

		SDL_FreeSurface(image);
		SDL_DestroyTexture(limage);
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