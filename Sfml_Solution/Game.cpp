#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Game::loadTiles()
{
	Animation staticAnim(0, 0, 1.0f);
	this->tileAtlas["hex"] =
		Tile(this->tileSize, 1, texmgr.getRef("hex"),
		{ staticAnim },
			TileType::HEX_GREEN);
	this->tileAtlas["grass"] =
		Tile(sf::Vector2u(800,600), 1, texmgr.getRef("grass"),
		{ staticAnim },
			TileType::CHARACTER); 
	this->tileAtlas["character"] =
		Tile(sf::Vector2u(48, 48), 1, texmgr.getRef("character"),
		{ Animation(0,7,0.2f) },
			TileType::CHARACTER);
}
void Game::loadTextures()
{
	std::string line;
	std::ifstream texFile("media/Textures.txt");
	if (texFile.is_open())
	{
		while (std::getline(texFile, line))
		{
			std::istringstream iss(line);
			std::vector<std::string> texPair((std::istream_iterator<std::string>(iss)),
				std::istream_iterator<std::string>());
			texmgr.loadTexture(texPair[0], texPair[1]);
		}
		texFile.close();
	}
}

void Game::loadFonts()
{
	sf::Font font;
	if (!font.loadFromFile("media/font.ttf"))
	{
		//Error
	}
	this->fonts["main_font"] = font;

	return;
}

void Game::loadStylesheets()
{
	this->stylesheets["button"] = GuiStyle(true, &this->fonts.at("main_font"), 1,
		sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00),
		sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00));
	this->stylesheets["text"] = GuiStyle(false, &this->fonts.at("main_font"), 0,
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff),
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));
	return;
}

void Game::pushState(GameState* state)
{
	this->states.push(state);
	return;
}

void Game::popState()
{
	delete this->states.top();
	this->states.pop();

	return;
}

void Game::changeState(GameState* state)
{
	if (!this->states.empty())
		popState();
	pushState(state);

	return;
}

GameState* Game::peekState()
{
	if (this->states.empty()) return nullptr;
	return this->states.top();
}

void Game::gameLoop()
{
	sf::Clock clock;

	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		this->window.clear(sf::Color::Black);
		peekState()->draw(dt);
		this->window.display();
	}
}

Game::Game()
{
	this->loadTextures();
	tileSize = sf::Vector2u(52, 60);
	this->loadTiles();
	this->loadFonts();
	this->loadStylesheets();
	this->window.create(sf::VideoMode(800, 600), "Game");
	this->window.setFramerateLimit(60);

	characterAtlas.push_back(new Character(Character::ClassType::KNIGHT));
	characterAtlas.push_back(new Character(Character::ClassType::MAGE));
	characterAtlas.push_back(new Character(Character::ClassType::ROGUE));
	characterAtlas.push_back(new Character(Character::ClassType::BARBARIAN));
	this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
	while (!this->states.empty()) popState();
}