#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Item
{
public:

	enum Suffix
	{

	};

	enum Affix
	{

	};

	enum Quality
	{
		BROKEN,
		RUSTED,
		GENERIC,
		FINE,
		PRISTINE,
		GODLY,
	};

	std::vector<Suffix> suf;
	std::vector<Affix> aff;
	Quality quality;
	
	sf::Text info;
	sf::Sprite invSprite;

	Item(sf::Texture& texture, Quality quality);
	~Item();
};

