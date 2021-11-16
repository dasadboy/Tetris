#pragma once

#include <vector>
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Block : sf::Shape {
	sf::Vector2f& position;
	sf::Color color;

public:

	explicit Block(sf::Vector2f& pos, sf::Color clr) : 
		position(pos), color(clr) {
		update();
	}

	void setPosition(const sf::Vector2f& pos) {
		position = pos;
		update();
	}

	virtual std::size_t getPointCount() const {
		return 4;
	}

	virtual sf::Vector2f getPoint(std::size_t idx) const {
		static std::vector<float> relPositionsX = {0, BLOCK::BLOCK_SIZE, 0, BLOCK::BLOCK_SIZE};
		static std::vector<float> relPositionsY = {0, 0, BLOCK::BLOCK_SIZE, BLOCK::BLOCK_SIZE};
		return sf::Vector2f(position.x + relPositionsX[idx], position.y + relPositionsY[idx]);
	}
};
