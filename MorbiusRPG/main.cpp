#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //Charge tout le SDL
		fprintf(stdout, "Echec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return -1;
	}

	if (IMG_Init(IMG_INIT_JPG) == 0) { //Charge le module JPG
		fprintf(stdout, "Echec de l'initialisation de la SDL Image (%s)\n", IMG_GetError());
		return -1;
	}

	if (TTF_Init() == -1) {
		fprintf(stdout, "Echec de l'initialisation de la SDL Ttf (%s)\n", TTF_GetError());
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

	int n_avaX = 0; //Pour la position du joueur en X
	int n_avaY = 0; //en Y

	int n_nbrFrame = 0; //Le nombre de frame totale
	int n_nbrFrameUneSeconde = 0; //Pour conna�tre les frames par secondes

	int n_FirstFrame = 0; //La premiere frame de la boucle 
	int delayTimer = 0; //Les ms pour le delay

	if (pWindow) { //Test si la fenetre marche

		if (renderer == NULL) //Test le renderer 
		{
			printf("Erreur lors de la creation d'un renderer (%s)", SDL_GetError());
			return -1;
		}

		SDL_Surface* image = IMG_Load("mdr.jpg"); //Cr�er une surface a partir de l'image
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

		TTF_Font* police = TTF_OpenFont("Game_Of_Squids.ttf", 16);
		if (police == NULL) {
			fprintf(stdout, "Erreur chargement de la police (%s)", TTF_GetError());
		}
		SDL_Color policeColeur = { 0, 255, 0, 255 }; //La couleur du texte
		char textFps[30] = ""; //Le texte qui sera affiche 
		char textNbrFps[30] = ""; //Le texte qui contient le nombre de FPS
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

			if (SDL_GetTicks() / 1000 > n_nbrFrame / 1000) { //Calcule si une seconde est passe
				//fprintf(stdout, "FPS : %d (%d)\n", n_nbrFrameUneSeconde, SDL_GetTicks()); //Affiche le nombre de frame dans la seconde precedente et affiche le nombre de ticks depuis le debut

				strcpy_s(textFps, "Fps : "); //Remet a jour le texte a afficher
				sprintf_s(textNbrFps, "%d", n_nbrFrameUneSeconde); //Transeforme le int en char
				strcat_s(textFps, textNbrFps); //Copy le char des fps dans le texte final

				n_nbrFrame = SDL_GetTicks(); //Remet le nbrFrame total remis a jour
				n_nbrFrameUneSeconde = 0; //Puis remet a 0 le nombre de frame dans une seconde
			}
			n_nbrFrameUneSeconde++; //Ajoute un frame par bouble

			SDL_Surface* TexteZone = TTF_RenderText_Solid(police, textFps, policeColeur); //Transeforme le texte en surface
			SDL_Texture* TexteZoneTex = SDL_CreateTextureFromSurface(renderer, TexteZone); //Puis en texture

			SDL_RenderClear(renderer); //Clean le renderer avant de le reafficher
			SDL_RenderCopy(renderer, limage, NULL, &posRec); //Met la position de l'image
			SDL_RenderCopy(renderer, TexteZoneTex, NULL, &posFps); //Affiche les FPS a l'ecran
			SDL_RenderPresent(renderer); //Puis affiche a l'ecran 

			SDL_FreeSurface(TexteZone); //D�truit la texture et la surface sinon surcharge
			SDL_DestroyTexture(TexteZoneTex);

			delayTimer = 16 - (SDL_GetTicks() - n_FirstFrame); //16 pour 60 fps - le temps de process
			if (delayTimer < 1) { //Si c'est en dessous de 1, le temps de process est trop long
				delayTimer = 16; //On remet a 16
			}

			SDL_Delay(delayTimer);
		}

		SDL_FreeSurface(image);
		SDL_DestroyTexture(limage);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(pWindow);

	}
	else {
		fprintf(stderr, "Erreur de cr�ation de la fen�tre: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Quit();
	return 0;

}