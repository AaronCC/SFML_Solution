#include "Knight.h"



Knight::Knight()
{
	this->skills.emplace(ATTACK, 4);
	this->skills.emplace(DEFENSE, 6);
	this->skills.emplace(CUNNING, 4);
	this->skills.emplace(KNOWLEDGE, 1);

	this->feats.emplace(MELEE, BASIC);
	this->feats.emplace(ARCHERY, NOVICE);
	this->feats.emplace(ARMOURER, BASIC);
	this->feats.emplace(RESISTANCE, NOVICE);
	this->feats.emplace(LUCK, NOVICE);
	this->feats.emplace(MYSTICISM, NOVICE);
}


Knight::~Knight()
{
}