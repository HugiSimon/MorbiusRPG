#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>
#include <random>

class JoueurAttack
{
public:
	JoueurAttack();

	bool mainAttack();
	void AttackEnnemie();
	bool choisirAttack();
	void Affichage();
	void petitAffichage(SDL_Renderer* renderer, TTF_Font* police);

private:
	SDL_Rect posi;
	int PV;
	std::map<std::string, int>attack;
	int PVEnnemie;
	int NumAttack;
	int list[5];
	bool antiRepeat;
	int puisAttack;
	int puisAttackE;
	int ticks;

};