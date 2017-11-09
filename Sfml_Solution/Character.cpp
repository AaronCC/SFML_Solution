#include "Character.h"

Character::Character(ClassType type)
{
	switch (type)
	{
	case KNIGHT:
		initStats(5, 7, 2, 1, BASIC, NOVICE, BASIC, NOVICE, NOVICE, NOVICE);
		break;
	case BARBARIAN:
		initStats(8, 5, 1, 1, BASIC, NOVICE, NOVICE, BASIC, NOVICE, NOVICE);
			break;
	case MAGE:
		initStats(1, 1, 5, 8, NOVICE, NOVICE, NOVICE, NOVICE, BASIC, BASIC);
		break;
	case ROGUE:
		initStats(7, 2, 5, 1, BASIC, BASIC, NOVICE, NOVICE, NOVICE, NOVICE);
		break;
	}
	this->type = type;
}

void Character::initInventory(sf::Texture& invBack, sf::Texture& slotBack, sf::Texture& slotBackH, GuiStyle* textStyle)
{
	this->inventory = new Inventory(invBack, slotBack, slotBackH, textStyle);
}

void Character::initStats(int att, int def, int cun, int kno,
	Aptitude mel, Aptitude arc, Aptitude arm, Aptitude res, Aptitude luck, Aptitude mys)
{
	skills.emplace(ATTACK, att);
	skills.emplace(DEFENSE, def);
	skills.emplace(CUNNING, cun);
	skills.emplace(KNOWLEDGE, kno);

	feats.emplace(MELEE, mel);
	feats.emplace(ARCHERY, arc);
	feats.emplace(ARMOURER, arm);
	feats.emplace(RESISTANCE, res);
	feats.emplace(LUCK, luck);
	feats.emplace(MYSTICISM, mys);
}

Character::~Character()
{

}