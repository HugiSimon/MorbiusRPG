#include "JoueurAttack.h"

JoueurAttack::JoueurAttack()
{
	this->attack["Coup de poing"] = 15;
	this->attack["Coup de pied"] = 20;
	this->attack["Coup de pompe"] = 200;

	this->perso = NULL;

	this->posi.x = 0;
	this->posi.y = 0;
	this->posi.w = 0;
	this->posi.h = 0;

	this->PV = 150;

	this->PVEnnemie = 100;
}

int JoueurAttack::mainAttack()
{
	this->PVEnnemie = this->PVEnnemie - choisirAttack();
	petitAffichage();
	this->PV = this->PV - AttackEnnemie();
	petitAffichage();

	if (this->PV < 1) {
		return 0;
	}
	return 1;
}

int JoueurAttack::AttackEnnemie()
{
	return rand() % 20;
}

int JoueurAttack::choisirAttack()
{
	return 0;
}

void JoueurAttack::Affichage()
{
}

void JoueurAttack::petitAffichage()
{
}
