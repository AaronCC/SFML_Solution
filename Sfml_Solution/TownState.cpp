#include "TownState.h"



void TownState::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.draw(this->game->background);
}

void TownState::update(const float dt)
{
}

void TownState::handleInput()
{
}

TownState::TownState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	this->background = sf::Sprite(this->game->texmgr.getRef("background"));
}


TownState::~TownState()
{
}
