#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class Map
{
public:
	Map();

	int Init(const char* tile, SDL_Renderer *Renderer);
	void MapTabl();
	int Texture(int idTile, int posX, int posY);

private:
	SDL_Texture* tile;
	SDL_Renderer* renderer;

};