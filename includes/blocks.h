#pragma once

#include "constants.h"

extern sf::RenderWindow window;

class Block {
	sf::RectangleShape block;

public:

	Block();

	Block(int row, int col);

	Block(int row, int col, sf::Color clr);

	void operator=(Block& newBlock);

	void setPos(sf::Vector2f& pos);

	void setPos(int row, int col);

	sf::Vector2f getPos();

	sf::RectangleShape& getShape();

	void draw();
};
