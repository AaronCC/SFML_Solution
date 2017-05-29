#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stack>

#include "TextureManager.h"
#include "Gui.h"
#include "Tile.h"
#include "Character.h"
#include "Knight.h"
#include "Mage.h"
#include "Rogue.h"
#include "Barbarian.h"

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
	sf::Sprite background;

	std::vector<Character*> characterAtlas;

	std::map<std::string, Tile> tileAtlas;
	std::map<std::string, GuiStyle> stylesheets;
	std::map<std::string, sf::Font> fonts;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();

	Game();
	~Game();
};

#endif /* GAME_H */