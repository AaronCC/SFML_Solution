#ifndef TOWN_STATE
#define TOWN_STATE

#include "GameState.h"

class TownState : public GameState
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt); 
	virtual void handleInput();

	sf::Sprite background;

	sf::View view;

	TownState(Game* game);
	~TownState();
};

#endif /* TOWN_STATE */