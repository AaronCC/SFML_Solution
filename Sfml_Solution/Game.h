#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stack>

#include "TextureManager.h"
#include "Gui.h"
#include "Tile.h"
#include "Character.h"
#include "ItemGenerator.h"

class GameState;

class Game
{
private:

	void loadTiles();
	void loadTextures();
	void loadStylesheets();
	void loadFonts();

public:

	const float aspectRatio = 800 / (float)600;

	sf::Vector2u tileSize;

	std::stack<GameState*> states;

	sf::RenderWindow window;
	TextureManager texmgr;
	ItemGenerator itGen;
	sf::Sprite background;

	std::vector<Character*> characterAtlas;

	std::map<std::string, Tile> tileAtlas;
	std::map<std::string, GuiStyle> stylesheets;
	std::map<std::string, sf::Font> fonts;

	Character* character;

	void initCharacter(int index, Gui infoGui)
	{
		character = characterAtlas.at(index);
		character->guiSystem.emplace("info", infoGui);
		character->initInventory(texmgr.getRef("inv_background"), texmgr.getRef("inv_slot"), texmgr.getRef("inv_slotH"), &this->stylesheets.at("text"));
	}
	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();
};

#endif /* GAME_H */