#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "AnimationHandler.h"

enum class TileType { HEX_GREEN, CHARACTER };

std::string tileTypeToStr(TileType type);

class Tile
{
public:

	AnimationHandler animHandler;

	sf::Vector2f position;
	sf::Sprite sprite;

	TileType tileType;

	/* Tile variant, allowing for different looking versions of the
	* same tile */
	int tileVariant;

	/* Constructor */
	Tile() { }
	Tile(sf::Vector2u tileSize, const unsigned int height, sf::Texture& texture,
		const std::vector<Animation>& animations,
		const TileType tileType)
	{
		sf::Vector2u size = texture.getSize();
		this->tileType = tileType;
		this->tileVariant = 0;
		this->sprite.setOrigin(sf::Vector2f(tileSize.x/2, tileSize.y/2));
		this->sprite.setTexture(texture);
		this->animHandler.frameSize = sf::IntRect(0, 0, tileSize.x, tileSize.y*height);
		for (auto animation : animations)
		{
			this->animHandler.addAnim(animation);
		}
		this->animHandler.update(0.0f);
	}

	void setPosition(sf::Vector2f position) { this->position = position; }

	void draw(sf::RenderWindow& window, float dt);

	void update();
};

#endif /* TILE_H */