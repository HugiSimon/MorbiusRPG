#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class JoueurLibre
{
public:
	JoueurLibre();

	int setTexture(const char *fichier, SDL_Renderer *renderer, int n_w, int n_h);
	void setPosition(int n_x, int n_y);
	void mouvement(SDL_Renderer *renderer, SDL_Rect coli[500]);
	void affichJoueur(SDL_Renderer *renderer);
	void destroyTexture();
	bool lanceCombat(int posX, int posY);

private:
	SDL_Texture* perso;
	SDL_Rect position;
	int vectX;
	int vectY;

};