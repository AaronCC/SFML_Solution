#include <SFML/Graphics.hpp>
#include <string>

#include "Gui.h"


sf::Vector2f Gui::getSize()
{
	return sf::Vector2f(this->dimensions.x, this->dimensions.y * this->entries.size());
}

int Gui::getEntry(const sf::Vector2f mousePos)
{
	/* If there are no entries then outside the menu */
	if (entries.size() == 0) return -1;
	if (!this->visible) return -1;

	for (int i = 0; i < this->entries.size(); ++i)
	{
		/* Translate point to use the entry's local coordinates*/
		sf::Vector2f point = mousePos;
		point += this->entries[i].shape.getOrigin();
		point -= this->entries[i].shape.getPosition();

		if (point.x < 0 || point.x > this->entries[i].shape.getScale().x*this->dimensions.x) continue;
		if (point.y < 0 || point.y > this->entries[i].shape.getScale().y*this->dimensions.y) continue;
		return i;
	}

	return -1;
}

void Gui::setEntryText(int entry, std::string text)
{
	if (entry >= entries.size() || entry < 0) return;

	entries[entry].text.setString(text);

	return;
}

void Gui::setDimensions(sf::Vector2f dimensions)
{
	this->dimensions = dimensions;

	for (auto& entry : entries)
	{
		entry.shape.setSize(dimensions);
		entry.text.setCharacterSize(dimensions.y - style.borderSize - padding);
	}

	return;
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!visible) return;

	/* Draw each entry of the menu */
	for (auto entry : this->entries)
	{
		/* Draw the entry */
		target.draw(entry.shape);
		target.draw(entry.text);
	}

	for (auto& image : this->images)
	{
		target.draw(image.sprite);
	}
	return;
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->background);
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			target.draw(this->equipped[r][c].back);
}

void Gui::show()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->visible = true;

	/* Draw each entry of the menu */
	for (auto& entry : this->entries)
	{
		/* Set the origin of the entry */
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		entry.shape.setOrigin(origin);
		entry.text.setOrigin(origin);
		/* Compute the position of the entry */
		sf::Vector2f centerPos = this->getPosition();
		if (this->style.centered)
			centerPos.x += (entry.shape.getSize().x / 2) - (entry.text.getLocalBounds().width / 2);
		entry.shape.setPosition(this->getPosition());
		entry.text.setPosition(centerPos);
		if (this->horizontal) offset.x += this->dimensions.x;
		else offset.y += this->dimensions.y;
	}
	for (auto& image : this->images)
	{
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		image.sprite.setPosition(this->getPosition());
		image.sprite.setOrigin(origin);
		if (this->horizontal) offset.x += this->dimensions.x;
		else offset.y += this->dimensions.y;
	}
	return;
}

void Inventory::show()
{
	sf::Vector2f origin = this->getOrigin();
	sf::Vector2f position = this->getPosition();
	this->background.setPosition(position);
	position.x += this->PADD;
	position.y += this->PADD;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			equipped[r][c].back.setOrigin(origin);
			equipped[r][c].back.setPosition(position);
			position.x += CELLW;
		}
		position.x -= 3 * CELLW;
		position.y += CELLW;
	}
	for (auto& item : this->inventory)
	{

	}
}

void Gui::hide()
{
	this->visible = false;

	return;
}

/* Highlights an entry of the menu */
void Gui::highlight(const int entry)
{
	for (int i = 0; i < entries.size(); ++i)
	{
		if (i == entry || entries[i].selected)
		{
			entries[i].shape.setFillColor(style.bodyHighlightCol);
			entries[i].shape.setOutlineColor(style.borderHighlightCol);
			entries[i].text.setFillColor(style.textHighlightCol);
		}
		else
		{
			entries[i].shape.setFillColor(style.bodyCol);
			entries[i].shape.setOutlineColor(style.borderCol);
			entries[i].text.setFillColor(style.textCol);
		}
	}

	return;
}

/* Return the message bound to the entry */
std::string Gui::activate(const int entry)
{
	if (entry == -1) return "null";
	return entries[entry].message;
}

std::string Gui::activate(sf::Vector2f mousePos)
{
	int entry = this->getEntry(mousePos);
	return this->activate(entry);
}

void Gui::selectOne(const int index)
{
	for (auto& entry : entries)
	{
		entry.selected = false;
		entry.shape.setFillColor(style.bodyCol);
		entry.shape.setOutlineColor(style.borderCol);
		entry.text.setFillColor(style.textCol);
	}
	entries[index].selected = true;
	entries[index].shape.setFillColor(style.bodyHighlightCol);
	entries[index].shape.setOutlineColor(style.borderHighlightCol);
	entries[index].text.setFillColor(style.textHighlightCol);
	return;
}