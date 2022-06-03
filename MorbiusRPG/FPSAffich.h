#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


class FPSAffich
{
public:
	FPSAffich();

	char* CalculFPS();
	void affichFPS(const char *fps, SDL_Renderer *renderer, SDL_Rect position, TTF_Font *police, SDL_Color couleur);

private:
	int n_nbrFrame;
	int n_nbrFrameUneSeconde;
	char textFPS[30];
	char textNbrFPS[30];

};