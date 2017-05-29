#include "StartState.h"
#include "GridState.h"
#include "NewGameState.h"
void StartState::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	for (auto gui : this->guiSystem) this->game->window.draw(gui.second);

	return;
}

void StartState::update(const float dt)
{
}

void StartState::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view);

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
		case sf::Event::Resized:
		{
			sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
			this->view.setSize(pos);
			break;
		}
		/* Highlight menu items */
		case sf::Event::MouseMoved:
		{
			this->guiSystem.at("menu").highlight(this->guiSystem.at("menu").getEntry(mousePos));
			break;
		}
		/* Click on menu items */
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::string msg = this->guiSystem.at("menu").activate(mousePos);

				if (msg == "load_game")
				{
					this->loadgame();
				}
			}
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break;
		}
		default: break;
		}
	}

	return;
}

void StartState::loadgame()
{
	//this->game->pushState(new GameStateEditor(this->game));
	this->game->pushState(new NewGameState(this->game));
	return;
}

StartState::StartState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	sf::Vector2f size(192, 32);
/*
	std::vector<sf::Texture*> images = std::vector<sf::Texture*>();
	images.push_back(&game->texmgr.getRef("portrait_1"));*/

	this->guiSystem.emplace("menu", Gui(sf::Vector2f(size.x, size.y), 4, false, game->stylesheets.at("button"),
	{ std::make_pair("Load Game", "load_game") }, {}));
	this->guiSystem.at("menu").setPosition(pos);
	this->guiSystem.at("menu").setOrigin((size.x / 2), (size.y / 2));
	this->guiSystem.at("menu").show();
	//this->guiSystem.at("menu2").setPosition(pos);
	//this->guiSystem.at("menu2").setOrigin(96, 32 * 1 / 2);
	//this->guiSystem.at("menu2").show();
}