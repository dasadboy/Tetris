#include "blocks.h"


#define translateRow2Disp(row) DISPLAY::SIZE_Y - (row + 1) * BLOCK::BLOCK_SIZE + BLOCK::OUTLINE_SIZE
#define translateCol2Disp(col) col * BLOCK::BLOCK_SIZE + BLOCK::OUTLINE_SIZE

Block::Block() {
	this->block = BLOCK::COMMON_BLOCK;
	this->block.setPosition(sf::Vector2f(0, 0));
	this->block.setOutlineColor(sf::Color::Black);
	this->block.setFillColor(sf::Color::Black);
}

Block::Block(int row, int col) {
	this->block = BLOCK::COMMON_BLOCK;
	this->block.setPosition(sf::Vector2f(translateCol2Disp(col), translateRow2Disp(row)));
	this->block.setOutlineColor(sf::Color::Black);
	this->block.setFillColor(sf::Color::Black);
}

Block::Block(int row, int col, sf::Color& clr) {
	this->block = BLOCK::COMMON_BLOCK;
	this->block.setPosition(sf::Vector2f(translateCol2Disp(col), translateRow2Disp(row)));
	this->block.setFillColor(clr);
	this->block.setOutlineColor(sf::Color::White);
	this->block.setOutlineThickness(BLOCK::OUTLINE_SIZE);
}

void Block::operator=(const Block& newBlock) {
	this->block = newBlock.block;
}

void Block::setPos(sf::Vector2f& pos) {
	this->block.setPosition(pos);
}

void Block::setPos(int row, int col) {
	this->block.setPosition(translateCol2Disp(col), translateRow2Disp(row));
}

const sf::Vector2f& Block::getPos() const {
	return this->block.getPosition();
}

const sf::RectangleShape& Block::getShape() const {
	return this->block;
}

void Block::draw(sf::RenderWindow& window) const {
	window.draw(this->block);
}
