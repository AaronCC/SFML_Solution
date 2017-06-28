#ifndef NEW_GAME_STATE_H
#define NEW_GAME_STATE_H

#include "GameState.h"
#include "Character.h"

class NewGameState : public GameState
{
private:
	Game* game;
	sf::View view;
	std::map<const std::string, Gui> guiSystem;
	//Inventory* inventory;
	const std::string classes[4] = { "Knight", "Mage", "Rogue", "Barbarian" };

	enum PlayerClass {
		KNIGHT = 0,
		MAGE = 1,
		ROGUE = 2,
		BARBARIAN = 3,
		NONE
	};

	PlayerClass selected;
	Character* character;

public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	void resizeView(float windowW, float windowH);
	std::string aptitudeToString(Character::Aptitude feat);
	void setInfoText(PlayerClass classType);
	virtual void handleInput();


	NewGameState(Game* game);
};

#endif /* NEW_GAME_STATE_H */