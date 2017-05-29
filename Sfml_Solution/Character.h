#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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

	std::map<Feat, Aptitude> feats;
	std::map<Skill, int> skills;
	std::string name;

	Character();
	~Character();
};
#endif
