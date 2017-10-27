#include "Item.h"

Item::Item(sf::Texture & texture, Quality quality)
{
	this->invSprite = sf::Sprite(texture);
	this->quality = quality;
}

Item::~Item()
{

}
