#ifndef GRID_STATE_H
#define GRID_STATE_H

#include "GameState.h"
#include "Game.h"
#include "Map.h"

class GridState : public GameState
{
private:

	sf::View gameView;
	sf::View guiView;
	std::map<std::string, Gui> guiSystem;
	std::map<sf::Keyboard::Key, bool> keyStates;

	Map* map;
public:
	void draw(const float dt);
	virtual void update(const float dt);
	void resizeView(float windowW, float windowH);
	virtual void handleInput();
	void handleKeyPress(sf::Keyboard::Key type);
	GridState(Game* game);
};

#endif /* GRID_STATE_H */