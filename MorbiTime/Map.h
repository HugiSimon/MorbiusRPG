#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <SDL_ttf.h>
#include <math.h>


class Map {
public:
	Map();
	~Map();

	void map();
	int texture(int idTile, int posx, int posy);
	void Initialisation();
	void render();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};