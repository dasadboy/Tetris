#include "blocks.h"


#define translateRow2Disp(row) DISPLAY::SIZE_Y - row * BLOCK::BLOCK_SIZE + BLOCK::OUTLINE_SIZE
#define translateCol2Disp(col) col * BLOCK::BLOCK_SIZE + BLOCK::OUTLINE_SIZE

Block::Block(int row, int col) {
	this->block = BLOCK::COMMON_BLOCK;
	this->block.setPosition(sf::Vector2f(translateCol2Disp(col), translateRow2Disp(row)));
	this->block.setOutlineColor(sf::Color::Black);
	this->block.setFillColor(sf::Color::Black);
}

Block::Block(int row, int col, sf::Color clr) {
	this->block = BLOCK::COMMON_BLOCK;
	this->block.setPosition(sf::Vector2f(translateCol2Disp(col), translateRow2Disp(row)));
	this->block.setOutlineColor(sf::Color::White);
}

void Block::operator=(Block& newBlock) {
	sf::RectangleShape newShape = newBlock.block;
	block = newShape;
}

void Block::setPos(sf::Vector2f& pos) {
	this->block.setPosition(pos);
}

void Block::setPos(int row, int col) {
	this->block.setPosition(translateCol2Disp(col), translateRow2Disp(row));
}

sf::Vector2f Block::getPos() {
	return this->block.getPosition();
}

sf::RectangleShape& Block::getShape() {
	return this->block;
}

void Block::draw() {
	window.draw(this->block);
}
