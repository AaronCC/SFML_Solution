#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <utility>
#include <string>
#include "Item.h"

enum SlotType {
	LEFT_HAND = 0,
	HEAD = 1,
	RIGHT_HAND = 2,
	GLOVES = 3,
	BODY = 4,
	CLOAK = 5,
	ACC1 = 6,
	FEET = 7,
	ACC2 = 8,
	INV = 9,
	ARR = 10
};

class GuiStyle
{
public:

	sf::Color bodyCol;
	sf::Color bodyHighlightCol;
	sf::Color borderCol;
	sf::Color borderHighlightCol;
	sf::Color textCol;
	sf::Color textHighlightCol;
	sf::Font* font;

	float borderSize;
	bool centered;

	GuiStyle(bool centered, sf::Font* font, float borderSize,
		sf::Color bodyCol, sf::Color borderCol, sf::Color textCol,
		sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol)
	{
		this->centered = centered;
		this->bodyCol = bodyCol;
		this->borderCol = borderCol;
		this->textCol = textCol;
		this->bodyHighlightCol = bodyHighlightCol;
		this->borderHighlightCol = borderHighlightCol;
		this->textHighlightCol = textHighlightCol;
		this->font = font;
		this->borderSize = borderSize;
	}
	GuiStyle() { }
};

class GuiEntry
{
public:
	bool selected;

	/* Handles appearance of the entry */
	sf::RectangleShape shape;

	/* String returned when the entry is activated */
	std::string message;

	/* Text displayed on the entry */
	sf::Text text;

	GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
	{
		this->message = message;
		this->shape = shape;
		this->text = text;
		this->selected = false;
	}
	GuiEntry() { }
};

class GuiImage
{
public:
	sf::Sprite sprite;
	sf::Vector2f dimensions;

	GuiImage(sf::Texture& texture)
	{
		this->sprite.setTexture(texture);
		dimensions.x = texture.getSize().x;
		dimensions.y = texture.getSize().y;
	}
	GuiImage() { }
};

class InvSlot {
public:
	sf::Sprite back;
	sf::Texture* backT;
	sf::Texture* backTH;

	bool selected;
	void Select() {
		if (selected)
			this->back.setTexture(*backT);
		else
			this->back.setTexture(*backTH);
		selected = !selected;
	}

	sf::Vector2f dimensions;
	SlotType type;
	Item* item;

	InvSlot() {}

	InvSlot(sf::Texture& back, sf::Texture& backH, sf::Vector2f dimensions, SlotType type) {
		this->selected = false;
		this->dimensions = dimensions;
		this->back = sf::Sprite(back);
		this->backT = &back;
		this->backTH = &backH;
		this->type = type;
	}

	void Equip(Item& item)
	{
		this->item = &item;
		this->item->invSprite.setOrigin(this->back.getOrigin());
		this->item->invSprite.setPosition(this->back.getPosition());
	}
};

class Gui : public sf::Transformable, public sf::Drawable
{
private:

	/* If true the menu entries will be horizontally, not vertically, adjacent */
	bool horizontal;

	GuiStyle style;

	sf::Vector2f dimensions;

	int padding;

public:

	std::vector<GuiEntry> entries;
	std::vector<GuiImage> images;

	bool visible;

	/* Constructor */
	Gui(sf::Vector2f dimensions, int padding, bool horizontal,
		GuiStyle& style, std::vector<std::pair<std::string, std::string>> entries, std::vector<sf::Texture*> images)
	{
		visible = false;
		this->horizontal = horizontal;
		this->style = style;
		this->dimensions = dimensions;
		this->padding = padding;

		/* Construct the background shape */
		sf::Sprite sprite;
		sf::RectangleShape shape;
		shape.setSize(dimensions);
		shape.setFillColor(style.bodyCol);
		shape.setOutlineThickness(-style.borderSize);
		shape.setOutlineColor(style.borderCol);

		/* Construct each gui entry */
		for (auto entry : entries)
		{
			/* Construct the text */
			sf::Text text;
			text.setString(entry.first);
			text.setFont(*style.font);
			text.setFillColor(style.textCol);
			text.setCharacterSize(dimensions.y - style.borderSize - padding);
			this->entries.push_back(GuiEntry(entry.second, shape, text));
		}
		for (auto image : images)
		{
			this->images.push_back(GuiImage(*image));
		}
	}

	sf::Vector2f getSize();

	/* Return the entry that the mouse is hovering over. Returns
	* -1 if the mouse if outside of the Gui */
	int getEntry(const sf::Vector2f mousePos);

	/* Change the text of an entry */
	void setEntryText(int entry, std::string text);

	/* Change the entry dimensions */
	void setDimensions(sf::Vector2f dimensions);

	/* Draw the menu */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void show();

	void hide();

	/* Highlights an entry of the menu */
	void highlight(const int entry);

	/* Return the message bound to the entry */
	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePos);

	void selectOne(const int index);
};
class Inventory : public sf::Transformable, public sf::Drawable {

public:
	int PADD;
	int CELLW;
	const sf::Vector2u SIZE = sf::Vector2u(320, 320);
	InvSlot equipped[3][3];
	sf::Sprite background;
	sf::Vector2f invPos;
	std::vector<InvSlot> inventory;
	std::pair<InvSlot, InvSlot> arrows;
	InvSlot* selected;
	int invAt;

	Inventory(sf::Texture& background, sf::Texture& back, sf::Texture& backH, sf::Texture& arrowL, sf::Texture& arrowR)
	{
		invAt = 0;
		this->background = sf::Sprite(background);
		sf::Vector2u backSize = background.getSize();
		PADD = 10;
		CELLW = (backSize.x - (2 * PADD)) / 5;
		int typeInd = 0;
		invPos = sf::Vector2f(PADD + CELLW, PADD + (3.5f * CELLW));
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				equipped[r][c] = InvSlot(back, backH, sf::Vector2f(CELLW, CELLW), SlotType(typeInd));
				typeInd++;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			inventory.push_back(InvSlot(back, backH, sf::Vector2f(CELLW, CELLW), INV));
		}
		arrows.first = InvSlot(arrowL, arrowL, sf::Vector2f(CELLW, CELLW), ARR);
		arrows.second = InvSlot(arrowR, arrowR, sf::Vector2f(CELLW, CELLW), ARR);
	}

	void Select(InvSlot& slot)
	{
		if (this->selected != nullptr)
			this->selected->Select();
		slot.Select();
		this->selected = &slot;
	}

	InvSlot * getInvSlot(const sf::Vector2f mousePos);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void show();

};

#endif /* GUI_H */