#pragma once
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define TAILLE 100
SDL_Texture* test;

Game::Game()
{
	this->i = 0;
	this->c = 0;
}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf_s("Erreur");

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer,0, 0, 0, 0);
		}
		isRunning = true;
	}

	else {
		isRunning = false;
	}
	
	SDL_Surface* perso = IMG_Load("tile.png");
	test = SDL_CreateTextureFromSurface(renderer, perso);
	SDL_FreeSurface(perso);	
}

void Game::map() {
	FILE* fEntrer = NULL;
	FILE* fSORTIE = NULL;
	char* cSaisie = (char*)malloc(TAILLE * sizeof(char));
	int n_val = 0;
	int value = 0;
	int mapc[500];
	int map[500];
	int test = 500;
	errno_t err;
	int map1[25][20] = {  };
	int map2[25][20] = {  };

	if (err = fopen_s(&fSORTIE, "level1.txt", "r") != 0) {
		fprintf_s(stderr, "Erreur\n", err);
	}
	else {
		int n_value[500];
		char sec1, sec2, sep;
		fscanf_s(fSORTIE, "%c", &sec1, 1);
		for (int i = 0; i < 500; i++) {
			//int value = 0;
			fscanf_s(fSORTIE, "%d", &map[i]);
			fscanf_s(fSORTIE, "%c", &sep, 1);
		}
		fscanf_s(fSORTIE, "%c", &sec2, 1);
	}
	int a = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 20; j++) {
			map1[i][j] = map[a];
			texture(map1[i][j], i, j);
			a++;
		}

	}

	if (fSORTIE)
		fclose(fSORTIE);


	if (err = fopen_s(&fEntrer, "collision.txt", "r") != 0) {
		fprintf_s(stderr, "Erreur\n", err);
	}
	else {

		char sec1, sec2, sep;
		fscanf_s(fEntrer, "%c", &sec1, 1);
		for (int i = 0; i < 500; i++) {
			//int value = 0;
			fscanf_s(fEntrer, "%d", &mapc[i]);
			fscanf_s(fEntrer, "%c", &sep, 1);
		}
		fscanf_s(fEntrer, "%c", &sec2, 1);
	}

	int c = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 20; j++) {
			map2[i][j] = mapc[c];
			texture(map2[i][j], i, j);
			c++;
		}

	}
	if (fEntrer)
		fclose(fEntrer);
}
int Game::texture(int idTile, int POSx, int POSy) {
	if (idTile == -1) {
		return 0;
	}
	SDL_Rect Ptile;
	SDL_Rect Coor;

	Ptile.x = idTile % 8 * 32;
	Ptile.y = idTile / 8 * 32;
	Ptile.w = 32;
	Ptile.h = 32;

	Coor.x = POSx % 25 * 32;
	Coor.y = POSy % 133 * 32;
	Coor.w = 32;
	Coor.h = 32;

	SDL_RenderCopy(renderer, test, &Ptile, &Coor);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
void Game::update()
{
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



