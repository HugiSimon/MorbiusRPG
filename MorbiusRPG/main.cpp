#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>

#include "Start.h"
#include "FPSAffich.h"
#include "JoueurLibre.h"
#include "JoueurAttack.h"

int main(int argc, char** argv) {

	Start Tout;
	FPSAffich FPS;
	JoueurLibre JoueurL;
	JoueurAttack JoueurA;
	bool Libre = false;

	if (Tout.startAll() == -1) {
		return -1;
	}
	SDL_Window *pWindow = Tout.createWindow("MorbiusRPG", 800, 480);
	SDL_Renderer* renderer = Tout.createRenderer(pWindow, -1);
	if (Tout.testAll(pWindow, renderer) == -1) {
		return -1;
	}

	int n_FirstFrame = 0; //La premiere frame de la boucle 
	int delayTimer = 0; //Les ms pour le delay

	JoueurL.setTexture("devant.png", renderer, 48, 60);
	JoueurL.setPosition(200, 50);

	JoueurA.chargetexture(renderer, "derriere.png", "devant_ennemie.png", "combat_nature.png");

	TTF_Font* policeSquid = TTF_OpenFont("Game_Of_Squids.ttf", 64);
	TTF_Font* policeCoolvectica = TTF_OpenFont("coolvetica-compressed-hv.ttf", 64);
	if (policeSquid == NULL && policeCoolvectica == NULL) {
		fprintf(stdout, "Erreur chargement de la police (%s)", TTF_GetError());
		return -1;
	}
	SDL_Color policeColeur = { 0, 255, 0, 255 }; //La couleur du texte
	SDL_Rect posFps = {0, -8, 150, 50}; //La position d'affichage

	while (true) { //La boucle principal de gameplay

		SDL_RenderClear(renderer); //Clean le renderer avant de le reafficher
		n_FirstFrame = SDL_GetTicks();

		if (Libre) {
			JoueurL.mouvement(renderer);
			JoueurL.affichJoueur(renderer);
		}
		else {
			if (JoueurA.choisirAttack()) {
				JoueurA.AttackEnnemie();
			}
			Libre = JoueurA.mainAttack();
			JoueurA.Affichage(renderer, policeCoolvectica);
			JoueurA.petitAffichage(renderer, policeCoolvectica);
		}

		FPS.affichFPS(FPS.CalculFPS(), renderer, posFps, policeSquid, policeColeur);

		SDL_RenderPresent(renderer); //Puis affiche a l'ecran 

		delayTimer = 16 - (SDL_GetTicks() - n_FirstFrame); //16 pour 60 fps - le temps de process
		if (delayTimer < 0) { //Si c'est en dessous de 1, le temps de process est trop long
			delayTimer = 0; //On remet a 0
		}

		if (Tout.End() == -1) {
			break;
		}

		SDL_Delay(delayTimer);

	}

	JoueurL.destroyTexture();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(pWindow);

	SDL_Quit();
	return 0;

}