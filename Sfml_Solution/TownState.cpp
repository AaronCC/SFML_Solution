#include "TownState.h"
#define BUTTON_GUI "button_gui"
#define BUTTON_HEIGHT 35
#define BUTTON_WIDTH 175

void TownState::draw(const float dt)
{
	this->game->window.setView(this->view);
	this->game->window.draw(this->game->background);
	if (this->selected == INVENTORY)
		this->game->window.draw(*this->game->character->inventory);
	else if (this->selected == SKILLS)
		this->game->window.draw(this->game->character->guiSystem.at("info"));
	for (auto gui : this->guiSystem) this->game->window.draw(gui.second);
}

void TownState::update(const float dt)
{
}

void TownState::handleInput()
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
			resizeView(event.size.width, event.size.height);
			break;
		}
		/* Highlight menu items */
		case sf::Event::MouseMoved:
		{
			this->guiSystem.at(BUTTON_GUI).highlight(this->guiSystem.at(BUTTON_GUI).getEntry(mousePos));
			break;
		}
		/* Click on menu items */
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::string buttonMsg = this->guiSystem.at(BUTTON_GUI).activate(mousePos);
				if (buttonMsg == "skills_button")
				{
					this->selected = SKILLS;
				}
				if (buttonMsg == "inventory_button")
				{
					this->selected = INVENTORY;
				}
				if (buttonMsg != "null")
				{
					this->guiSystem.at(BUTTON_GUI).selectOne(this->guiSystem.at(BUTTON_GUI).getEntry(mousePos));
				}

				InvSlot* invSlot = this->game->character->inventory->getInvSlot(mousePos);
				if (invSlot != nullptr)
				{
					this->game->character->inventory->Select(*invSlot);
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

TownState::TownState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
	this->background = sf::Sprite(this->game->texmgr.getRef("background"));
	sf::Vector2f guiPadding(50.f, 50.f);
	this->guiSystem.emplace(
		BUTTON_GUI,
		Gui(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT), 6, false,
			game->stylesheets.at("button"),
			{
				std::make_pair("Skills", "skills_button"),
				std::make_pair("Abilities", "abilities_button"),
				std::make_pair("Inventory", "inventory_button")
			}, {}));
	this->guiSystem.at(BUTTON_GUI).setPosition(guiPadding);
	this->guiSystem.at(BUTTON_GUI).setOrigin(0, 0);
	this->guiSystem.at(BUTTON_GUI).show();
	sf::Vector2f invPos(BUTTON_WIDTH + (2 * guiPadding.x), guiPadding.y);

	this->game->character->inventory->setPosition(invPos);
	this->game->character->inventory->show();

	this->game->character->guiSystem.at("info").setPosition(invPos);
	this->game->character->guiSystem.at("info").show();
}

TownState::~TownState()
{
}
