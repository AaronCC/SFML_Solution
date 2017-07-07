#include "NewGameState.h"
#include "GridState.h"

#pragma region definitions
#define CLASS_GUI "classes"
#define CHOOSE_TEXT_GUI "choose_class"
#define PORTRAITS_GUI "portraits"
#define BUTTON_HEIGHT 25

#define DONE_GUI "done"

#define INFO_GUI "info"
#define INFO_HEIGHT 25

#define CLASS_ENTRY 0
#pragma endregion
#pragma endregion

NewGameState::NewGameState(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	selected = NONE;
	initGui();
}

void NewGameState::initGui()
{
	sf::Vector2f portraitPos = sf::Vector2f(30, 50);

	std::map<std::string, std::vector<sf::Texture*>> images;
	std::vector<sf::Texture*> textures;
	textures.push_back(&game->texmgr.getRef("portrait_1"));
	textures.push_back(&game->texmgr.getRef("portrait_2"));
	textures.push_back(&game->texmgr.getRef("portrait_3"));
	textures.push_back(&game->texmgr.getRef("portrait_4"));
	images.emplace(PORTRAITS_GUI, textures);
	textures.clear();

	sf::Vector2u portraitSize = images.at(PORTRAITS_GUI)[0]->getSize();
	for (auto image : images)
	{
		sf::Vector2f size = sf::Vector2f();
		size.x = image.second[0]->getSize().x;
		size.y = image.second[0]->getSize().y;
		this->guiSystem.emplace(PORTRAITS_GUI, Gui(size, 0, true, game->stylesheets.at("button"), {}, image.second));
		this->guiSystem.at(PORTRAITS_GUI).setPosition(sf::Vector2f(size.x / 2 + portraitPos.x, size.y / 2 + portraitPos.y));
		this->guiSystem.at(PORTRAITS_GUI).setOrigin((size.x / 2), (size.y / 2));
		this->guiSystem.at(PORTRAITS_GUI).show();
	}

	this->guiSystem.emplace(CLASS_GUI, Gui(sf::Vector2f(portraitSize.x, BUTTON_HEIGHT), 4, true, game->stylesheets.at("button"),
	{
		std::make_pair("Knight", classes[KNIGHT]),
		std::make_pair("Mage", classes[MAGE]),
		std::make_pair("Rogue", classes[ROGUE]),
		std::make_pair("Barbarian", classes[BARBARIAN])
	}, {}));

	this->guiSystem.at(CLASS_GUI).setPosition(sf::Vector2f(portraitPos.x, portraitSize.y + portraitPos.y));
	this->guiSystem.at(CLASS_GUI).setOrigin(0, 0);
	this->guiSystem.at(CLASS_GUI).show();

	this->guiSystem.emplace(CHOOSE_TEXT_GUI, Gui(sf::Vector2f(portraitSize.x, BUTTON_HEIGHT), 0, true, game->stylesheets.at("text"),
	{ std::make_pair("Choose your class", CHOOSE_TEXT_GUI) }, {}));
	this->guiSystem.at(CHOOSE_TEXT_GUI).setPosition(sf::Vector2f(portraitPos.x, portraitPos.x / 2));
	this->guiSystem.at(CHOOSE_TEXT_GUI).setOrigin(0, 0);
	this->guiSystem.at(CHOOSE_TEXT_GUI).show();

	this->guiSystem.emplace(INFO_GUI, Gui(sf::Vector2f(portraitSize.x, INFO_HEIGHT),
		8, false, game->stylesheets.at("text"),
		{
			std::make_pair("Class: ", "class_info"),
			std::make_pair("\nAttack: ", "attack_info"),
			std::make_pair("\nArmour: ", "armour_info"),
			std::make_pair("\nCunning: ", "cunning_info"),
			std::make_pair("\nKnowledge: ", "cunning_info"),
			std::make_pair("\nMelee: ", "melee_info"),
			std::make_pair("\nArchery: ", "archery_info"),
			std::make_pair("\nArmourer: ", "armourer_info"),
			std::make_pair("\nResistance: ", "resistance_info"),
			std::make_pair("\nLuck: ", "luck_info"),
			std::make_pair("\nMysticism: ", "mysticism_info"),
		}, {}));

	this->guiSystem.at(INFO_GUI).setPosition(sf::Vector2f(portraitPos.x, portraitPos.y + portraitSize.y + (2 * BUTTON_HEIGHT)));
	this->guiSystem.at(INFO_GUI).setOrigin(0, 0);
	this->guiSystem.at(INFO_GUI).show();

	this->guiSystem.emplace(DONE_GUI, Gui(sf::Vector2f(portraitSize.x, INFO_HEIGHT),
		4, false, game->stylesheets.at("button"),
		{
			std::make_pair("Done", "done_button")
		}, {}));

	this->guiSystem.at(DONE_GUI).setPosition(sf::Vector2f(portraitPos.x + portraitSize.x * 3, portraitPos.y + portraitSize.y + (2 * BUTTON_HEIGHT)));
	this->guiSystem.at(DONE_GUI).setOrigin(0, 0);
	this->guiSystem.at(DONE_GUI).show();
}

void NewGameState::draw(const float dt)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	for (auto gui : this->guiSystem) this->game->window.draw(gui.second);

	return;
}

void NewGameState::update(const float dt)
{
	return;
}

std::string NewGameState::aptitudeToString(Character::Aptitude aptitude)
{
	switch (aptitude)
	{
	case Character::Aptitude::NOVICE:
		return "Novice";
	case Character::Aptitude::BASIC:
		return "Basic";
	case Character::Aptitude::ADVANCED:
		return "Advanced";
	case Character::Aptitude::EXPERT:
		return "Expert";
	}
	return "NULL";
}

void NewGameState::setInfoText(PlayerClass classType)
{
	this->guiSystem.at(INFO_GUI).setEntryText(Character::Skill::ATTACK, "\nAttack: " +
		std::to_string(this->game->characterAtlas[classType]->skills[Character::Skill::ATTACK]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Skill::DEFENSE, "\nArmour: " +
		std::to_string(this->game->characterAtlas[classType]->skills[Character::Skill::DEFENSE]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Skill::CUNNING, "\nCunning: " +
		std::to_string(this->game->characterAtlas[classType]->skills[Character::Skill::CUNNING]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Skill::KNOWLEDGE, "\nKnowledge: " +
		std::to_string(this->game->characterAtlas[classType]->skills[Character::Skill::KNOWLEDGE]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::MELEE + 4, "\nMelee: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::MELEE]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::ARCHERY + 4, "\nArchery: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::ARCHERY]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::ARMOURER + 4, "\nArmourer: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::ARMOURER]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::RESISTANCE + 4, "\nResistance: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::RESISTANCE]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::LUCK + 4, "\nLuck: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::LUCK]));

	this->guiSystem.at(INFO_GUI).setEntryText(Character::Feat::MYSTICISM + 4, "\nMysticism: " +
		aptitudeToString(this->game->characterAtlas[classType]->feats[Character::Feat::MYSTICISM]));
}

void NewGameState::handleInput()
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
			this->guiSystem.at(CLASS_GUI).highlight(this->guiSystem.at(CLASS_GUI).getEntry(mousePos));
			this->guiSystem.at(DONE_GUI).highlight(this->guiSystem.at(DONE_GUI).getEntry(mousePos));
			break;
		}
		/* Click on menu items */
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::string class_msg = this->guiSystem.at(CLASS_GUI).activate(mousePos);
				if (class_msg == classes[KNIGHT]) {
					setInfoText(KNIGHT);
					selected = KNIGHT;
				}
				else if (class_msg == classes[MAGE]) {
					setInfoText(MAGE);
					selected = MAGE;
				}
				else if (class_msg == classes[ROGUE]) {
					setInfoText(ROGUE);
					selected = ROGUE;
				}
				else if (class_msg == classes[BARBARIAN]) {
					setInfoText(BARBARIAN);
					selected = BARBARIAN;
				}
				else if (this->guiSystem.at(DONE_GUI).activate(mousePos) == "done_button")
				{
					this->game->initCharacter(selected, this->guiSystem.at(INFO_GUI));
					this->game->pushState(new TownState(this->game));
				}
				if (class_msg != "null")
				{
					this->guiSystem.at(INFO_GUI).setEntryText(CLASS_ENTRY, "Class: " + classes[selected]);
					this->guiSystem.at(CLASS_GUI).selectOne(this->guiSystem.at(CLASS_GUI).getEntry(mousePos));
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