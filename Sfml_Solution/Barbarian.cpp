#include "Barbarian.h"



Barbarian::Barbarian()
{
	this->skills.emplace(ATTACK, 7);
	this->skills.emplace(DEFENSE, 5);
	this->skills.emplace(CUNNING, 2);
	this->skills.emplace(KNOWLEDGE, 1);

	this->feats.emplace(MELEE, BASIC);
	this->feats.emplace(ARCHERY, NOVICE);
	this->feats.emplace(ARMOURER, NOVICE);
	this->feats.emplace(RESISTANCE, BASIC);
	this->feats.emplace(LUCK, NOVICE);
	this->feats.emplace(MYSTICISM, NOVICE);
}

Barbarian::~Barbarian()
{
}
