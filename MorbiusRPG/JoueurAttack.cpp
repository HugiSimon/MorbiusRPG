#include "JoueurAttack.h"

JoueurAttack::JoueurAttack()
{
	this->listNom[0] = "Coup de poing";
	this->listNom[1] = "Coup de pied";
	this->listNom[2] = "Coup de pompe";

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

	this->perso = NULL;
	this->ennemie = NULL;

	this->background = NULL;
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
					this->antiRepeat = false;
					break;
				case SDLK_DOWN:
					if (this->NumAttack < 2) {
						this->NumAttack++;
					}
					this->antiRepeat = false;
					break;
				case SDLK_RETURN:
					this->PVEnnemie = this->PVEnnemie - this->list[NumAttack];
					this->puisAttack = this->list[NumAttack];
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

void JoueurAttack::Affichage(SDL_Renderer* renderer, TTF_Font* police)
{
	SDL_Rect tempRect = { 0, 0, 800, 640 };
	SDL_RenderCopy(renderer, this->background, NULL, &tempRect);
	
	tempRect = { 25, 560, 204, 64 };
	SDL_SetRenderDrawColor(renderer, 204, 10, 10, 255);
	SDL_RenderFillRect(renderer, &tempRect);

	switch (this->NumAttack)
	{
	case 0:
		tempRect = { 27, 562, 200, 20 };
		break;
	case 1:
		tempRect = { 27, 582, 200, 20 };
		break;
	case 2:
		tempRect = { 27, 602, 200, 20 };
		break;
	default:
		break;
	}
	SDL_SetRenderDrawColor(renderer, 17, 17, 17, 255);
	SDL_RenderFillRect(renderer, &tempRect);

	if (this->PV > 0 && this->PVEnnemie > 0) {

		tempRect = { 75, 510, 104, 14 };
		SDL_RenderFillRect(renderer, &tempRect);
		tempRect = { 77,512,this->PV * 100 / 150,10 };
		SDL_SetRenderDrawColor(renderer, 252, 60, 63, 255);
		SDL_RenderFillRect(renderer, &tempRect);

		tempRect = { 650, 150, 104, 14 };
		SDL_SetRenderDrawColor(renderer, 17, 17, 17, 255);
		SDL_RenderFillRect(renderer, &tempRect);
		tempRect = { 652, 152, this->PVEnnemie, 10 };
		SDL_SetRenderDrawColor(renderer, 252, 60, 63, 255);
		SDL_RenderFillRect(renderer, &tempRect);

	}

	tempRect = { 28, 564, 100, 16 };
	SDL_Color tempColor = { 255, 255, 255, 255 };
	for (int n_i = 0; n_i < 3; n_i++) {
		SDL_Surface *tempSurface = TTF_RenderText_Solid(police, this->listNom[n_i].c_str(), tempColor);
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_RenderCopy(renderer, tempTexture, NULL, &tempRect);
		SDL_FreeSurface(tempSurface);
		SDL_DestroyTexture(tempTexture);

		
		char tempDegat[30];
		sprintf_s(tempDegat, "%d", this->list[n_i]);
		SDL_Surface *tempSurface2 = TTF_RenderText_Solid(police, tempDegat, tempColor);
		SDL_Texture *tempTexture2 = SDL_CreateTextureFromSurface(renderer, tempSurface2);
		tempRect.x = 198;
		tempRect.w = 30;
		SDL_RenderCopy(renderer, tempTexture2, NULL, &tempRect);
		SDL_FreeSurface(tempSurface2);
		SDL_DestroyTexture(tempTexture2);
		tempRect.x = 28;
		tempRect.w = 100;

		tempRect.y += 20;
	}

	tempRect = { 80, 385, 96, 120 };
	SDL_RenderCopy(renderer, this->perso, NULL, &tempRect);

	tempRect = { 667, 50, 72, 96 };
	SDL_RenderCopy(renderer, this->ennemie, NULL, &tempRect);;

	SDL_SetRenderDrawColor(renderer, 68, 68, 68, 255);
}

void JoueurAttack::petitAffichage(SDL_Renderer* renderer, TTF_Font* police) //Pour afficher les degats faits ou recu 
{
	if (this->ticks + 1000 > SDL_GetTicks()) {
		SDL_Color tempColor = { 229, 11, 36, 255 };
		char tempDegat[30];
		sprintf_s(tempDegat, "%d", this->puisAttack);
		SDL_Surface* tempSurface = TTF_RenderText_Solid(police, tempDegat, tempColor);
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		this->posi = { 675, 82, 50, 50 };

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
			this->posi = { 102, 440, 50, 50 };

			if (this->puisAttackE == 1) {
				this->posi.x = 125;
				this->posi.w = 12;
			}
			if (this->puisAttackE > 1) {
				this->posi.x = 115;
				this->posi.w = 25;
			}
			if (this->puisAttackE > 9) {
				this->posi.x = 102;
				this->posi.w = 50;
			}

			this->posi.x += rand() % 6 - 3;

			SDL_RenderCopy(renderer, tempTexture, NULL, &posi);

			SDL_FreeSurface(tempSurface);
			SDL_DestroyTexture(tempTexture);
		}
	}
}

int JoueurAttack::chargetexture(SDL_Renderer* renderer, const char* perso, const char* ennemie, const char* background)
{
	SDL_DestroyTexture(this->perso);
	SDL_DestroyTexture(this->ennemie);

	SDL_Surface* tempSuface = IMG_Load(perso);
	SDL_PixelFormat *format = tempSuface->format;
	SDL_SetColorKey(tempSuface, SDL_TRUE, SDL_MapRGB(format, 0, 0, 0));
	this->perso = SDL_CreateTextureFromSurface(renderer, tempSuface);

	if (this->perso == NULL) {
		fprintf(stdout, "Erreur texture (%s)", SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(tempSuface);

	SDL_Surface* tempSuface2 = IMG_Load(ennemie);
	format = tempSuface2->format;
	SDL_SetColorKey(tempSuface2, SDL_TRUE, SDL_MapRGB(format, 0, 0, 0));
	this->ennemie = SDL_CreateTextureFromSurface(renderer, tempSuface2);

	if (this->ennemie == NULL) {
		fprintf(stdout, "Erreur texture (%s)", SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(tempSuface2);

	SDL_Surface* tempSuface3 = IMG_Load(background);
	this->background = SDL_CreateTextureFromSurface(renderer, tempSuface3);

	if (this->background == NULL) {
		fprintf(stdout, "Erreur texture (%s)", SDL_GetError());
		return -1;
	}

	SDL_FreeSurface(tempSuface3);


	return 0;
}
