#include "board.h"

#define translateRow(row) (std::max(0, (row) + BOARD::ROW_OFFSET))
#define translateCol(col) (std::max(0, std::min((col) + BOARD::COLUMN_OFFSET, BOARD::TRUE_ROW_SIZE - 1))) // returns 0 or 11 if !(0 < row + offset < 11)

const Block Board::BoardCell::defaultBlock = Block();

Board::Board() {
	this->board = std::vector<BoardCell>(BOARD::TRUE_BOARD_SIZE);
	this->blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	int row = BOARD::LEFT_BOUNDARY, col = BOARD::BOTTOM_BOUNDARY;

	for (int row = 0; row < BOARD::COLUMN_SIZE; ++row) {
		for (int col = 0; col < BOARD::ROW_SIZE; ++col) {
			BoardCell& cell = board[translateRow(row) * BOARD::TRUE_ROW_SIZE + translateCol(col)];
			cell.block.setPos(row, col);
		}
	}
	
	// set beginning and end of each row as buffer
	for (int row = 0; row < BOARD::TRUE_COLUMN_SIZE; ++row) {
		this->board[row * BOARD::TRUE_ROW_SIZE].isOccupied = true;
		this->board[row * BOARD::TRUE_ROW_SIZE + BOARD::TRUE_ROW_SIZE - 1].isOccupied = true;
	}
	for (int col = 0, size = BOARD::TRUE_ROW_SIZE; col < size; ++col) {
		this->board[col].isOccupied = true;
	}
}

Board::BoardCell& Board::operator[] (int rowCol){
	return board[translateRow(rowCol / BOARD::ROW_SIZE) * BOARD::TRUE_ROW_SIZE + translateCol(rowCol % 10)];
}

Board::BoardCell& Board::operator[] (indices rowCol) {
	return board[translateRow(rowCol.i) * BOARD::TRUE_ROW_SIZE + translateCol(rowCol.j)];
}

// true if occupied
bool Board::checkPositionLegal(int row, int col) {
	int rowTranslated = translateRow(row), colTranslated = translateCol(col);
	return (this->board[rowTranslated * BOARD::TRUE_ROW_SIZE + colTranslated].isOccupied);
}

int Board::removeFilledRows(int rowStart) {
	// Copy all unfilled rows from rowStart to currentHeight to an unfilled row
	int currRow = translateRow(rowStart), srcRow = translateRow(rowStart), score = 0;
	while (currRow <= BOARD::VISIBLE_HEIGHT) {
		if (this->blocksPerRow[srcRow] == BOARD::ROW_SIZE) {
			++srcRow, ++score; // Skip this row as it is full and should not be in the result
		}
		else {
			// copy srcRow to currRow
			int currCell = currRow * BOARD::TRUE_ROW_SIZE + translateCol(0), currCellEnd = currCell + BOARD::ROW_SIZE,
				srcCell = srcRow * BOARD::TRUE_ROW_SIZE + translateCol(0);

			this->blocksPerRow[currRow] = this->blocksPerRow[srcRow];

			for (; currCell < currCellEnd; ++currCell, ++srcCell) {
				this->board[currCell] = this->board[srcCell];
			}

			++currRow, ++srcRow;
		}
	}

	return score;
}

int Board::setPiece(std::vector<int>& rows, std::vector<int>& cols, std::vector<Block>& blocks) {

	BoardCell& cell0 = this->board[translateRow(rows[0]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[0])];
	BoardCell& cell1 = this->board[translateRow(rows[1]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[1])];
	BoardCell& cell2 = this->board[translateRow(rows[2]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[2])];
	BoardCell& cell3 = this->board[translateRow(rows[3]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[3])];

	cell0.block = blocks[0];
	cell0.isOccupied = true;
	++this->blocksPerRow[translateRow(rows[0])];

	cell1.block = blocks[1];
	cell1.isOccupied = true;
	++this->blocksPerRow[translateRow(rows[1])];

	cell2.block = blocks[2];
	cell2.isOccupied = true;
	++this->blocksPerRow[translateRow(rows[2])];

	cell3.block = blocks[3];
	cell3.isOccupied = true;
	++this->blocksPerRow[translateRow(rows[3])];

	return removeFilledRows(*std::min_element(rows.begin(), rows.end()));
}

void Board::draw(sf::RenderWindow& window) {
	for (int row = 0; row <= BOARD::VISIBLE_HEIGHT; ++row) {
		for (int col = 0; col < BOARD::ROW_SIZE; ++col) {
			this->board[translateRow(row) * BOARD::TRUE_ROW_SIZE + translateCol(col)].block.draw(window);
		}
	}
}

bool Board::checkGameOver() {
	return this->blocksPerRow[translateRow(20)] >= 1;
}
