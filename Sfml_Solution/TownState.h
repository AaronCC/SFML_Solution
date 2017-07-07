#ifndef TOWN_STATE
#define TOWN_STATE

#include "GameState.h"
#include "ItemGenerator.h"

class TownState : public GameState
{
public:
	enum ButtonType
	{
		NONE,
		SKILLS,
		INVENTORY
	};

	virtual void draw(const float dt);
	virtual void update(const float dt); 
	virtual void handleInput();

	ButtonType selected;
	ItemGenerator itGen;
	std::map<const std::string, Gui> guiSystem;
	
	sf::Sprite background;

	TownState(Game* game);
	~TownState();
};

#endif /* TOWN_STATE */