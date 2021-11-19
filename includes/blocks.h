#pragma once

#include "constants.h"

class Block {
	sf::RectangleShape block;

public:

	Block(int row, int col);

	Block(int row, int col, sf::Color clr);

	void setPos(sf::Vector2f& pos);

	void setPos(int row, int col);

	sf::Vector2f getPos();

	sf::RectangleShape& getShape();
};
