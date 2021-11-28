#pragma once

#include "constants.h"

class Block {
	sf::RectangleShape block;

public:

	Block();

	Block(int row, int col);

	Block(int row, int col, sf::Color clr);

	void operator=(Block& newBlock);

	void setPos(sf::Vector2f& pos);

	void setPos(int row, int col);

	const sf::Vector2f& getPos() const;

	const sf::RectangleShape& getShape() const;

	void draw(sf::RenderWindow& window) const;
};
