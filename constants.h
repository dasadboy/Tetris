#pragma once
#include <vector>

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
}

namespace COLOR { 

	const int COLOR_EMPTY = 0;
	
	const int COLOR_SQUARE = 1;

	const int COLOR_LBLOCKL = 2;

	const int COLOR_LBLOCKR = 3;

	const int COLOR_TBLOCK = 4;

	const int COLOR_ZBLOCK = 5;

	const int COLOR_SBLOCK = 6;

	const int COLOR_STRAIGHT = 7;
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

	const int OUT_OF_BOUNDS_SENTINEL = -1;
}