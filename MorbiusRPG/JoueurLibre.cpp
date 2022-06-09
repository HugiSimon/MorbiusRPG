#include "JoueurLibre.h"

JoueurLibre::JoueurLibre()
{
	this->perso = NULL;
	this->position.h = 0;
	this->position.w = 0;
	this->position.x = 0;
	this->position.y = 0;
	this->vectX = 0;
	this->vectY = 0;
}

int JoueurLibre::setTexture(const char* fichier, SDL_Renderer *renderer, int n_w, int n_h)
{
	SDL_Surface* tempSurface = IMG_Load(fichier);
	if (tempSurface == NULL) {
		fprintf(stdout, "Erreur chargement de l'image (%s)", IMG_GetError());
		return -1;
	}
	destroyTexture();
	this->perso = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (this->perso == NULL) {
		fprintf(stdout, "Erreur chargement de la texture (%s)", SDL_GetError());
		return -1;
	}

	this->position.w = n_w;
	this->position.h = n_h;

	SDL_FreeSurface(tempSurface);

	return 0;
}

void JoueurLibre::setPosition(int n_x, int n_y)
{
	this->position.x = n_x;
	this->position.y = n_y;
}

void JoueurLibre::mouvement(SDL_Renderer* renderer)
{
	SDL_Event tempEvent;
	if (SDL_PollEvent(&tempEvent)) {

		if (SDL_KEYDOWN) {
			switch (tempEvent.key.keysym.sym) {
				case SDLK_UP:
					this->vectY = -2;
					setTexture("derriere.png", renderer, 32, 40);
					break;
				case SDLK_DOWN:
					this->vectY = 2;
					setTexture("devant.png", renderer, 32, 40);
					break;
				case SDLK_LEFT:
					this->vectX = -2;
					setTexture("gauche.png", renderer, 32, 40);
					break;
				case SDLK_RIGHT:
					this->vectX = 2;
					setTexture("droite.png", renderer, 32, 40);
					break;
				default:
					break;
			}
		}

		switch (tempEvent.key.state) {
			case SDL_RELEASED:
				this->vectX = 0;
				this->vectY = 0;
				break;
			default:
				break;
		}
	}

	this->position.x = this->position.x + this->vectX;
	this->position.y = this->position.y + this->vectY;
}

void JoueurLibre::affichJoueur(SDL_Renderer *renderer)
{
	SDL_SetTextureBlendMode(this->perso, SDL_BLENDMODE_ADD);
	SDL_RenderCopy(renderer, this->perso, NULL, &this->position);
}

void JoueurLibre::destroyTexture()
{
	SDL_DestroyTexture(this->perso);
}