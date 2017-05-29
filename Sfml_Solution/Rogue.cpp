#include "Rogue.h"



Rogue::Rogue()
{
	this->skills.emplace(ATTACK, 5);
	this->skills.emplace(DEFENSE, 1);
	this->skills.emplace(CUNNING, 7);
	this->skills.emplace(KNOWLEDGE, 2);

	this->feats.emplace(MELEE, BASIC);
	this->feats.emplace(ARCHERY, NOVICE);
	this->feats.emplace(ARMOURER, NOVICE);
	this->feats.emplace(RESISTANCE, NOVICE);
	this->feats.emplace(LUCK, BASIC);
	this->feats.emplace(MYSTICISM, NOVICE);
}


Rogue::~Rogue()
{
}
