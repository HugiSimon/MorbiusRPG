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

	int mainAttack();
	int AttackEnnemie();
	int choisirAttack();
	void Affichage();
	void petitAffichage();

private:
	SDL_Texture* perso;
	SDL_Rect posi;
	int PV;
	std::map<std::string, int>attack;
	int PVEnnemie;

};