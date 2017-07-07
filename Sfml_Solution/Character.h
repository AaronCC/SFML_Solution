#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Gui.h"

class Character
{
public:

	enum Skill {
		ATTACK = 1,
		DEFENSE = 2,
		CUNNING = 3,
		KNOWLEDGE = 4
	};

	enum Aptitude {
		NOVICE = 0,
		BASIC = 1,
		ADVANCED = 2,
		EXPERT = 3
	};

	enum Feat {
		MELEE = 1,
		ARCHERY = 2,
		ARMOURER = 3,
		RESISTANCE = 4,
		LUCK = 5,
		MYSTICISM = 6
	};

	enum ClassType {
		KNIGHT,
		MAGE,
		ROGUE,
		BARBARIAN
	};

	std::map<Feat, Aptitude> feats;
	std::map<Skill, int> skills;
	std::string name;
	Inventory* inventory;
	std::map<std::string, Gui> guiSystem;
	ClassType type;

	Character(ClassType type);
	void initInventory(sf::Texture & invBack, sf::Texture & slotBack, sf::Texture & slotBackH, sf::Texture & arrowL, sf::Texture & arrowR);
	
	void initStats(int att, int def, int cun, int kno, Aptitude mel, Aptitude arc, Aptitude arm, Aptitude res, Aptitude luck, Aptitude mys);
	~Character();
};
#endif
