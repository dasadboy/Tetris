#pragma once

#include <vector>
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Block : sf::Shape {
	sf::Vector2f& position;
	sf::Color color;

public:

	explicit Block(sf::Vector2f& pos, sf::Color clr);

	void setPosition(const sf::Vector2f& pos);

	virtual std::size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t idx) const;
};
