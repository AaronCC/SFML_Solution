#include <SFML/Graphics.hpp>
#include "Game.h"
#include "StartState.h"

int main()
{
	Game game;

	game.pushState(new StartState(&game));
	game.gameLoop();

	return 0;
}