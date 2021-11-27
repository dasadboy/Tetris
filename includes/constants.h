#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

namespace PIECES {

	const int NUMBER_OF_PIECES = 7;

	const int INITIAL_ABS_POSITION_X = 5;

	const int INITIAL_ABS_POSITION_Y = 20;

	const int INITIAL_ROTATION = 0;

	const int MOVE_UP = 1;

	const int MOVE_DOWN = -1;

	const int MOVE_LEFT = -1;

	const int MOVE_RIGHT = 1;

	const int STATES_OF_ROTATION = 4;

	const int NUMBER_OF_BLOCKS = 4;
}

namespace COLOR { 
	
	const sf::Color COLOR_OPIECE = sf::Color::Yellow;

	const sf::Color COLOR_JPIECE = sf::Color::Blue;

	const sf::Color COLOR_LPIECE = sf::Color::Red + sf::Color::Yellow; // Orange doesn't exist

	const sf::Color COLOR_TPIECE = sf::Color::Red + sf::Color::Blue; // Purple doesn't exist

	const sf::Color COLOR_ZPIECE = sf::Color::Red;

	const sf::Color COLOR_SPIECE = sf::Color::Green;

	const sf::Color COLOR_IPIECE = sf::Color::Cyan;
}

namespace BOARD {

	const int ROW_SIZE = 10;

	const int TRUE_ROW_SIZE = 12;

	const int COLUMN_SIZE = 40;

	const int TRUE_COLUMN_SIZE = 41;

	const int BOARD_SIZE = (ROW_SIZE) * (COLUMN_SIZE);

	const int TRUE_BOARD_SIZE = (TRUE_ROW_SIZE) * (TRUE_COLUMN_SIZE); // extra row and 2 columns for buffer

	const int COLUMN_OFFSET = 1;

	const int ROW_OFFSET = 1;

	const int LEFT_BOUNDARY = 1;

	const int RIGHT_BOUNDARY = 10;

	const int BOTTOM_BOUNDARY = 1;

	const int RIGHT_ONE_COLUMN = 1;

	const int LEFT_ONE_COLUMN = -1;

	const int DOWN_ONE_ROW = -10;

	const int UP_ONE_ROW = 10;
}

namespace DISPLAY {

	const unsigned int SIZE_X = 200;

	const unsigned int SIZE_Y = 400;
}

namespace BLOCK {

	const int NUMBER_OF_POINTS = 4;

	const float BLOCK_SIZE = 20;

	const float INNER_SIZE = 18;

	const float OUTLINE_SIZE = 1;

	const sf::RectangleShape COMMON_BLOCK = sf::RectangleShape(sf::Vector2f(INNER_SIZE, INNER_SIZE));
}

namespace TIME {

	const int PASSIVE_TIME_CUTOFF = 1.f;

	const int PIECE_MOVE_COOLDOWN = .2f;

}
