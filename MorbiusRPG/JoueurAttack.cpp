#include "JoueurAttack.h"

JoueurAttack::JoueurAttack()
{
	this->attack["Coup de poing"] = 15;
	this->attack["Coup de pied"] = 20;
	this->attack["Coup de pompe"] = 200;

	this->NumAttack = 0;

	this->list[0] = 15;
	this->list[1] = 20;
	this->list[2] = 200;

	this->posi.x = 0;
	this->posi.y = 0;
	this->posi.w = 0;
	this->posi.h = 0;

	this->PV = 150;

	this->PVEnnemie = 100;

	this->antiRepeat = true;

	this->puisAttack = 0;
	this->puisAttackE = 0;

	this->ticks = NULL;

}

bool JoueurAttack::mainAttack()
{	
	if (this->PV < 1 || this->PVEnnemie < 1) {
		return true;
	}
	return false;
}

void JoueurAttack::AttackEnnemie()
{
	int temp = rand() % 25;
	this->PV = this->PV - temp;
	this->puisAttackE = temp;
	fprintf(stdout, "PV : %d\n", this->PV);
}

bool JoueurAttack::choisirAttack()
{
	SDL_Event tempEvent;
	if (SDL_PollEvent(&tempEvent)) {
		if (this->antiRepeat) {
			if (SDL_KEYDOWN) {
				switch (tempEvent.key.keysym.sym) {
				case SDLK_UP:
					if (this->NumAttack > 0) {
						this->NumAttack--;
					}

					fprintf(stdout, "NumAttack : %d\n", this->NumAttack);
					this->antiRepeat = false;
					break;
				case SDLK_DOWN:
					if (this->NumAttack < 2) {
						this->NumAttack++;
					}

					fprintf(stdout, "NumAttack : %d\n", this->NumAttack);
					this->antiRepeat = false;
					break;
				case SDLK_RETURN:
					this->PVEnnemie = this->PVEnnemie - this->list[NumAttack];
					this->puisAttack = this->list[NumAttack];
					fprintf(stdout, "PVEnnemie : %d\n", this->PVEnnemie);
					this->antiRepeat = false;
					this->ticks = SDL_GetTicks();
					return true;
					break;
				default:
					break;
				}
			}
		}
		switch (tempEvent.key.state) {
		case SDL_RELEASED:
			this->antiRepeat = true;
			break;
		default:
			break;
		}
	}
	return false;
}

void JoueurAttack::Affichage()
{
	
}

void JoueurAttack::petitAffichage(SDL_Renderer* renderer, TTF_Font* police) //Pour afficher les degats faits ou recu 
{
	if (this->ticks + 1000 > SDL_GetTicks()) {
		SDL_Color tempColor = { 229, 11, 36, 255 };
		char tempDegat[30];
		sprintf_s(tempDegat, "%d", this->puisAttack);
		SDL_Surface* tempSurface = TTF_RenderText_Solid(police, tempDegat, tempColor);
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		this->posi = { 50, 350, 50, 50 };

		this->posi.x += rand() % 6 - 3;

		SDL_RenderCopy(renderer, tempTexture, NULL, &posi);

		SDL_FreeSurface(tempSurface);
		SDL_DestroyTexture(tempTexture);
	}
	else {
		if (this->ticks + 2000 > SDL_GetTicks()) {
			SDL_Color tempColor = { 229, 11, 36, 255 };
			char tempDegat[30];
			sprintf_s(tempDegat, "%d", this->puisAttackE);
			SDL_Surface* tempSurface = TTF_RenderText_Solid(police, tempDegat, tempColor);
			SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
			this->posi = { 700, 100, 25, 50 };

			if (this->puisAttackE == 1) {
				this->posi.w = 7;
			}
			if (this->puisAttackE > 1) {
				this->posi.w = 25;
			}
			if (this->puisAttackE > 9) {
				this->posi.w = 50;
			}

			this->posi.x += rand() % 6 - 3;

			SDL_RenderCopy(renderer, tempTexture, NULL, &posi);

			SDL_FreeSurface(tempSurface);
			SDL_DestroyTexture(tempTexture);
		}
	}
}
