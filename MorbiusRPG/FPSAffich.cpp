#include "FPSAffich.h"

FPSAffich::FPSAffich()
{
	this->n_nbrFrame = 0;
	this->n_nbrFrameUneSeconde = 0;
	*this->textFPS = *"";
	*this->textNbrFPS = *"";
}

char* FPSAffich::CalculFPS()
{
	if (SDL_GetTicks() / 1000 > this->n_nbrFrame / 1000) {
		strcpy_s(this->textFPS, "FPS : ");
		sprintf_s(this->textNbrFPS, "%d", this->n_nbrFrameUneSeconde);
		strcat_s(this->textFPS, this->textNbrFPS);

		this->n_nbrFrame = SDL_GetTicks();
		this->n_nbrFrameUneSeconde = 0;
	}
	this->n_nbrFrameUneSeconde++;

	return this->textFPS;
}

void FPSAffich::affichFPS(const char* fps, SDL_Renderer *renderer, SDL_Rect position, TTF_Font *police, SDL_Color couleur)
{
	SDL_Surface* tempSurface = TTF_RenderText_Solid(police, fps, couleur);
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_RenderCopy(renderer, tempTexture, NULL, &position);

	SDL_FreeSurface(tempSurface);
	SDL_DestroyTexture(tempTexture);
}
