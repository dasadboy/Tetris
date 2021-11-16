#include "board.h"

#define translateRow(row) std::max(0, row + BOARD::ROW_OFFSET)
#define translateCol(col) std::max(0, std::min(col + BOARD::COLUMN_OFFSET, BOARD::TRUE_ROW_SIZE - 1)) // returns 0 or 11 if row + offset is not between 1 and 10

Board::Board() {
	this->board = std::vector<int>(BOARD::TRUE_BOARD_SIZE, 0);
	this->blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	this->currentHeight = 1;
	
	// place buffer at beginning and end of each row
	for (int row = 0, size = BOARD::TRUE_COLUMN_SIZE; row < size; ++row) {
		this->board[row * BOARD::TRUE_ROW_SIZE] = BOARD::OUT_OF_BOUNDS_SENTINEL;
		this->board[row * BOARD::TRUE_ROW_SIZE + BOARD::TRUE_ROW_SIZE - 1] = BOARD::OUT_OF_BOUNDS_SENTINEL;
	}
	for (int col = 0, size = BOARD::TRUE_ROW_SIZE; col < size; ++col) {
		this->board[col] = BOARD::OUT_OF_BOUNDS_SENTINEL;
	}
}

int& Board::operator[] (int rowCol){
	return board[translateRow(rowCol / BOARD::ROW_SIZE) * BOARD::TRUE_ROW_SIZE + translateCol(rowCol % 10)];
}

int& Board::operator[] (indices rowCol) {
	return board[translateRow(rowCol.i) * BOARD::TRUE_ROW_SIZE + translateCol(rowCol.j)];
}

// true if occupied
bool Board::checkPositionLegal(int row, int col) {
	int rowTranslated = translateRow(row), colTranslated = translateCol(col);
	return (this->board[rowTranslated * BOARD::TRUE_ROW_SIZE + colTranslated] != 0);
}

void Board::removeFilledRows(int rowStart) {
	// Copy all unfilled rows from rowStart to currentHeight to an unfilled row
	int currRow = translateRow(rowStart), srcRow = translateRow(rowStart), height = this->currentHeight;
	while (srcRow <= height) {
		if (this->blocksPerRow[srcRow] == BOARD::ROW_SIZE) {
			++srcRow; // Skip this row as it is full and should not be in the result
			--this->currentHeight;
		}
		else {
			// copy srcRow to currRow
			int currCell = currRow * BOARD::ROW_SIZE, currCellEnd = currRow + BOARD::ROW_SIZE,
				srcCell = srcRow * BOARD::ROW_SIZE, srcCellEnd = srcCell + BOARD::ROW_SIZE;

			this->blocksPerRow[currRow] = this->blocksPerRow[srcRow];

			for (; currCell < currCellEnd; ++currCell, ++srcCell) {
				this->board[currCell] = this->board[srcCell];
				this->board[srcCell] = 0;
			}

			++currRow, ++srcRow;
		}
	}
}

void Board::setPiece(std::vector<int> rows, std::vector<int> cols, int color) {
	this->currentHeight = *std::max_element(rows.begin(), rows.end());

	this->board[translateRow(rows[0]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[0])] = color;
	++this->blocksPerRow[translateRow(rows[0])];

	this->board[translateRow(rows[1]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[1])] = color;
	++this->blocksPerRow[translateRow(rows[1])];

	this->board[translateRow(rows[2]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[2])] = color;
	++this->blocksPerRow[translateRow(rows[2])];

	this->board[translateRow(rows[3]) * BOARD::TRUE_ROW_SIZE + translateCol(cols[3])] = color;
	++this->blocksPerRow[translateRow(rows[3])];
}

void Board::drawBlock(int row, int col) {
	
}

void Board::draw() {
	
}
