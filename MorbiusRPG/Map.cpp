#include "Map.h"

Map::Map()
{
	this->tile = NULL;

	this->renderer = NULL;
}

int Map::Init(const char* tile, SDL_Renderer *Renderer)
{
	SDL_Surface* tempSurface = IMG_Load(tile);
	this->tile = SDL_CreateTextureFromSurface(Renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (this->tile == NULL) {
		fprintf(stdout, "Erreur chargement de la texture (%s)", SDL_GetError());
		return -1;
	}

	this->renderer = Renderer;

	return 0;
}

void Map::MapTabl()
{
	FILE* fEntrer;
	FILE* fSortie;

	int mapc[500];
	int map[500];

	int map1[25][20] = {};
	int map2[25][20] = {};

	char sec1, sec2, sep;

	errno_t err;

	if (err = fopen_s(&fSortie, "level1.txt", "r") != 0) {
		fprintf(stderr, "Erreur\n");
	}
	else {
		fscanf_s(fSortie, "%d", &sec1);
		for (int i = 0; i < 500; i++) {
			fscanf_s(fSortie, "%d", &map[i]);
			fscanf_s(fSortie, "%c", &sep, 1);
		}
		fscanf_s(fSortie, "%c", &sec2, 1);
	}

	int a = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 20; j++) {
			map1[i][j] = map[a];
			Texture(map1[i][j], i, j);
			a++;
		}
	}
	if (fSortie) {
		fclose(fSortie);
	}


	if (err = fopen_s(&fEntrer, "collision.txt", "r") != 0) {
		fprintf(stderr, "Erreur\n");
	}
	else {
		fscanf_s(fEntrer, "%c", &sec1, 1);
		for (int i = 0; i < 500; i++) {
			fscanf_s(fEntrer, "%d", &mapc[i]);
			fscanf_s(fEntrer, "%c", &sep, 1);
		}
		fscanf_s(fEntrer, "%c", &sec2, 1);
	}

	a = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 20; j++) {
			map2[i][j] = mapc[a];
			Texture(map2[i][j], i, j);
			a++;
		}
	}
	if (fEntrer) {
		fclose(fEntrer);
	}
}

int Map::Texture(int idTile, int posX, int posY)
{
	if (idTile == -1) {
		return 0;
	}

	SDL_Rect Ptile = { idTile % 8 * 32, idTile / 8 * 32, 32, 32 };
	SDL_Rect Coor = { posX % 25 * 32, posY % 133 * 32, 32, 32 };

	SDL_RenderCopy(this->renderer, this->tile, &Ptile, &Coor);
}