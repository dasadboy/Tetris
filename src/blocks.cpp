#include "blocks.h"

Block::Block(sf::Vector2f& pos, sf::Color clr) :
	position(pos), color(clr) {
	this->setOutlineThickness(BLOCK::OUTLINE_SIZE);
	this->setOutlineColor(sf::Color::White);
	update();
}

void Block::setPosition(const sf::Vector2f& pos) {
	position = pos;
	update();
}

std::size_t Block::getPointCount() const {
	return 4;
}

sf::Vector2f Block::getPoint(std::size_t idx) const {
	static std::vector<float> relPositionsX = { BLOCK::OUTLINE_SIZE, BLOCK::OUTLINE_SIZE + BLOCK::INNER_SIZE, BLOCK::OUTLINE_SIZE, BLOCK::OUTLINE_SIZE + BLOCK::INNER_SIZE };
	static std::vector<float> relPositionsY = { BLOCK::OUTLINE_SIZE, BLOCK::OUTLINE_SIZE, BLOCK::OUTLINE_SIZE + BLOCK::INNER_SIZE, BLOCK::OUTLINE_SIZE + BLOCK::INNER_SIZE };
	return sf::Vector2f(position.x + relPositionsX[idx], position.y + relPositionsY[idx]);
}