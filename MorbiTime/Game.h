#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>




class Game {
public:
	
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	int texture(int idTile, int posx,int posy);
	void map();
	
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int i;
	int c;
	
	bool isRunning;
	
	
};