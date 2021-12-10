#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
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
	
	const sf::Color COLOR_OPIECE = sf::Color(0xff, 0xff, 0, 0xff); // Yellow

	const sf::Color COLOR_JPIECE = sf::Color(0, 0, 0xff, 0xff); //Blue

	const sf::Color COLOR_LPIECE = sf::Color(0xff, 0x80, 0, 0xff); // Orange 

	const sf::Color COLOR_TPIECE = sf::Color(0xff, 0, 0xff, 0xff); // Purple

	const sf::Color COLOR_ZPIECE = sf::Color(0xff, 0, 0, 0xff); // Red

	const sf::Color COLOR_SPIECE = sf::Color(0, 0xff, 0, 0xff); // Green

	const sf::Color COLOR_IPIECE = sf::Color(0, 0xff, 0xff, 0xff); // Cyan

}

namespace BOARD {

	const int ROW_SIZE = 10;

	const int TRUE_ROW_SIZE = 12;

	const int COLUMN_SIZE = 40;

	const int TRUE_COLUMN_SIZE = 41;

	const int VISIBLE_HEIGHT = 21;

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

	const float PASSIVE_TIME_CUTOFF = 1.f;

	const float PIECE_MOVE_COOLDOWN = .2f;

	const float RESULT_SCREEN_DURATION = 5.f;

	const int RESULT_SCREEN_ANIMATION_DURATION = 500; // In milliseconds

}

namespace RESULT_SCREEN {

	const std::string RESULT_SCREEN_FONT = "resources/resultScreenFont.ttf";

	const int GAME_OVER_TEXT_SIZE = 24;

	const int GAME_OVER_TEXT_VERTICAL_OFFSET = 2;

	const int SCORE_TEXT_SIZE = 18;

	const int SCORE_TEXT_VERTICAL_OFFSET = 28;

	const int RESULT_SCREEN_HORIZONTAL_OFFSET = 2;

	const float EVENT_CLOSE_OFFSET = 500;

}
