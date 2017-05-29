#include "Map.h"


void Map::draw(sf::RenderWindow & window, float dt)
{
	//sf::Vector2f pos = sf::Vector2f(400, 300);
	//background.sprite.setPosition(pos);
	//background.draw(window, dt);
	
	for (int y = 0; y < this->height; ++y)
	{
		for (int x = 0; x < this->width; ++x)
		{
			sf::Vector2f pos = sf::Vector2f(tileSize.x / (float)2, tileSize.y / (float)2);
			pos.x += (float)(tileSize.x * x);
			pos.y += (float)(tileSize.y * (3/(float)4)) * y;
			if (std::remainder(y, 2) != 0)
				pos.x += tileSize.x / 2;
			this->tiles[y*this->width + x].setPosition(pos);
			this->tiles[y*this->width + x].sprite.setPosition(pos);
			this->tiles[y*this->width + x].draw(window, dt);
		}
	}
	sf::Vector2f pos = sf::Vector2f(tileSize.x/2, tileSize.y/2);
	background.sprite.setPosition(pos);
	background.draw(window, dt);
	return;
}

void Map::loadMap()
{
	width = 10;
	height = 10;
	for (int y = 0; y < this->height; ++y)
	{
		for (int x = 0; x < this->width; ++x)
		{
			tiles.push_back(game->tileAtlas.at("hex"));
		}
	}
	tileSize.x = this->game->tileSize.x;
	tileSize.y = this->game->tileSize.y;
	background = this->game->tileAtlas["character"];
}


Map::Map(Game* game)
{
	this->game = game;
	this->tiles = std::vector<Tile>();
	loadMap();
}
Map::~Map()
{
}
	