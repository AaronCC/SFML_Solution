#include "GridState.h"

GridState::GridState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->gameView.setCenter(pos);
	
	keyStates.emplace(sf::Keyboard::Key::Left, false);
	keyStates.emplace(sf::Keyboard::Key::Right, false);
	keyStates.emplace(sf::Keyboard::Key::Up, false);
	keyStates.emplace(sf::Keyboard::Key::Down, false);
	map = new Map(game);
}

void GridState::draw(const float dt)
{
	this->game->window.setView(this->gameView);
	this->map->draw(this->game->window, dt);
}

void GridState::update(const float dt)
{
}

void GridState::resizeView(float windowW, float windowH)
{
	float windowRatio = windowW / (float)windowH;
	float viewRatio = this->game->aspectRatio;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	// If horizontalSpacing is true, the black bars will appear on the left and right side.
	// Otherwise, the black bars will appear on the top and bottom.

	if (horizontalSpacing) {
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	gameView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}
void GridState::handleInput()
{
	sf::Event event;
	sf::Vector2f pos;
	sf::Vector2f gamePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);
	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Resized:
		{
			pos = sf::Vector2f(this->game->window.getSize());
			resizeView( event.size.width, event.size.height); 
			break;
		}
		default:
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		keyStates[sf::Keyboard::Key::Left] = true;
	}
	else { keyStates[sf::Keyboard::Key::Left] = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		keyStates[sf::Keyboard::Key::Right] = true;
	}
	else { keyStates[sf::Keyboard::Key::Right] = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		keyStates[sf::Keyboard::Key::Down] = true;
	}
	else { keyStates[sf::Keyboard::Key::Down] = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		keyStates[sf::Keyboard::Key::Up] = true;
	}
	else { keyStates[sf::Keyboard::Key::Up] = false; }
	for (auto key : this->keyStates)
		if (key.second)
			handleKeyPress(key.first);
}

void GridState::handleKeyPress(sf::Keyboard::Key type)
{
	switch (type)
	{
	case sf::Keyboard::Key::Left:
		this->gameView.move(-1, 0);
		break;
	case sf::Keyboard::Key::Right:
		this->gameView.move(1, 0);
		break;
	case sf::Keyboard::Key::Up:
		this->gameView.move(0, -1);
		break;
	case sf::Keyboard::Key::Down:
		this->gameView.move(0, 1);
		break;
	}
}
