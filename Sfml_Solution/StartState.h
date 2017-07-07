#ifndef START_STATE_H
#define START_STATE_H

#include "GameState.h"

class StartState : public GameState
{
private:

	std::map<std::string, Gui> guiSystem;

	void loadgame();

public:

	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	StartState(Game* game);
};

#endif /* START_STATE_H */