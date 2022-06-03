#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Start.h"
#include "FPSAffich.h"

int main(int argc, char** argv) {

	Start Tout;
	FPSAffich FPS;

	if (Tout.startAll() == -1) {
		return -1;
	}
	SDL_Window *pWindow = Tout.createWindow("MorbiusRPG", 640, 480);
	SDL_Renderer* renderer = Tout.createRenderer(pWindow, -1);
	if (Tout.testAll(pWindow, renderer) == -1) {
		return -1;
	}

	int n_avaX = 0; //Pour la position du joueur en X
	int n_avaY = 0; //en Y

	int n_FirstFrame = 0; //La premiere frame de la boucle 
	int delayTimer = 0; //Les ms pour le delay

	SDL_Surface* image = IMG_Load("mdr.jpg"); //Créer une surface a partir de l'image
	if (image == NULL) {
		fprintf(stdout, "Erreur chargement de l'image (%s)", IMG_GetError());
		return -1;
	}

	SDL_Texture* limage = SDL_CreateTextureFromSurface(renderer, image); //Puis la transeforme en texture
	if (limage == NULL) {
		fprintf(stdout, "Erreur chargement de la texture (%s)", SDL_GetError());
		return -1;
	}
	SDL_Rect posRec = { 200, 0, 150, 235 }; //Creer un rectangle, permet de faire la position de l'image

	TTF_Font* police = TTF_OpenFont("Game_Of_Squids.ttf", 64);
	if (police == NULL) {
		fprintf(stdout, "Erreur chargement de la police (%s)", TTF_GetError());
		return -1;
	}
	SDL_Color policeColeur = { 0, 255, 0, 255 }; //La couleur du texte
	SDL_Rect posFps = {0, -8, 150, 50}; //La position d'affichage

	while (true) { //La boucle principal de gameplay

		n_FirstFrame = SDL_GetTicks();

		SDL_Event event; //Event capture toutes les inputs du pc
		if (SDL_PollEvent(&event)) { //Verifie qu'il sait passe quelque chose 
			if (event.type == SDL_QUIT) { 
				break;
			}

			if (SDL_KEYDOWN) { //Verifie qu'une touche est presse
				switch (event.key.keysym.sym) { //Recupere qu'elle touche puis change la variable en fonction
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

			switch (event.key.state) { //Teste l'etat du clavier
				case SDL_RELEASED: //Fin de touche presse // A FAIRE Rajouter un swith qui verifie qu'elle touche n'est plus presse 
					n_avaX = 0; //Puis remet les movement a 0
					n_avaY = 0;
					break;
				default:
					break;
			}
		}

		posRec.x = posRec.x + n_avaX; //Fait bouger le joueur, qu'il est une entree ou non
		posRec.y = posRec.y + n_avaY;

		SDL_RenderClear(renderer); //Clean le renderer avant de le reafficher
		SDL_RenderCopy(renderer, limage, NULL, &posRec); //Met la position de l'image
		FPS.affichFPS(FPS.CalculFPS(), renderer, posFps, police, policeColeur);
		SDL_RenderPresent(renderer); //Puis affiche a l'ecran 

		delayTimer = 16 - (SDL_GetTicks() - n_FirstFrame); //16 pour 60 fps - le temps de process
		if (delayTimer < 0) { //Si c'est en dessous de 1, le temps de process est trop long
			delayTimer = 0; //On remet a 0
		}

		SDL_Delay(delayTimer);
	}

	SDL_FreeSurface(image);
	SDL_DestroyTexture(limage);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(pWindow);

	SDL_Quit();
	return 0;

}