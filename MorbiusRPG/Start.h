#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

class Start
{
public:
	Start();
	
	int startAll();
	int startSDL();
	int startSDLImage();
	int startSDLTTF();

	SDL_Window* createWindow(const char *name, int n_w, int n_h);
	SDL_Renderer* createRenderer(SDL_Window *window, int index);

	int testAll(SDL_Window* window, SDL_Renderer* renderer);
	int testWindow(SDL_Window* window);
	int testRenderer(SDL_Renderer* renderer);

	int End();

private:

};
