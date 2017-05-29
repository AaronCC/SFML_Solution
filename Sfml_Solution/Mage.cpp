#include "Mage.h"



Mage::Mage()
{
	this->skills.emplace(ATTACK, 1);
	this->skills.emplace(DEFENSE, 1);
	this->skills.emplace(CUNNING, 6);
	this->skills.emplace(KNOWLEDGE, 7);

	this->feats.emplace(MELEE, NOVICE);
	this->feats.emplace(ARCHERY, NOVICE);
	this->feats.emplace(ARMOURER, NOVICE);
	this->feats.emplace(RESISTANCE, NOVICE);
	this->feats.emplace(LUCK, BASIC);
	this->feats.emplace(MYSTICISM, BASIC);
}


Mage::~Mage()
{
}
