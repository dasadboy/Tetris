#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	this->board = std::vector<int>(BOARD::BOARD_SIZE, 0);
	this->blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	this->currentHeight = 0;
	this->currentPiece = new Piece();
	this->absPiecePositionCol = 0;
	this->absPiecePositionRow = 0;
	this->rotation = 0;
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}


int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
}

inline int Board::getPieceCol(int i) {
	return this->absPiecePositionCol + (*(this->currentPiece->relXPositions))[rotation * 4 + i];
}

inline int Board::getPieceRow(int i) {
	return this->absPiecePositionRow + (*(this->currentPiece->relYPositions))[rotation * 4 + i];
}

inline int Board::getPieceRowCol(int i) {
	return 10 * this->absPiecePositionRow + this->absPiecePositionCol + (*(this->currentPiece->relXPositions))[rotation * 4 + i] + 10 * (*(this->currentPiece->relYPositions))[rotation * 4 + i];
}

bool Board::checkPieceOverlaps(int offsetX, int offsetY) {
	return (board[((getPieceRowCol(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
	    || (board[((getPieceRowCol(1) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
	    || (board[((getPieceRowCol(2) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
	    || (board[((getPieceRowCol(3) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0);
}

inline bool Board::checkOutOfBoundsRight(int offsetX) {
	return (getPieceCol(0) + offsetX > BOARD::RIGHT_BOUNDARY) || (getPieceCol(1) + offsetX > BOARD::RIGHT_BOUNDARY) || (getPieceCol(2) + offsetX > BOARD::RIGHT_BOUNDARY) || (getPieceCol(3) + offsetX > BOARD::RIGHT_BOUNDARY);
}

inline bool Board::checkOutOfBoundsLeft(int offsetX) {
	return (getPieceCol(0) + offsetX < BOARD::LEFT_BOUNDARY) || (getPieceCol(1) + offsetX < BOARD::LEFT_BOUNDARY) || (getPieceCol(2) + offsetX < BOARD::LEFT_BOUNDARY) || (getPieceCol(3) + offsetX < BOARD::LEFT_BOUNDARY);
}

inline bool Board::checkOutOfBoundsBelow(int offsetY) {
	return (getPieceRow(0) + offsetY < BOARD::BOTTOM_BOUNDARY) || (getPieceRow(1) + offsetY < BOARD::BOTTOM_BOUNDARY) || (getPieceRow(2) + offsetY < BOARD::BOTTOM_BOUNDARY) || (getPieceRow(3) + offsetY < BOARD::BOTTOM_BOUNDARY);
}

void Board::generateNewPiece() {
	delete this->currentPiece;
	this->currentPiece = this->pieceNames[rand() % PIECES::NUMBER_OF_PIECES]();
	this->absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->absPiecePositionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->rotation = PIECES::INITIAL_ROTATION;
}

void Board::generateNewPiece(Piece* piece) {
	delete this->currentPiece;
	this->currentPiece = piece;
	this->absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->absPiecePositionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->rotation = PIECES::INITIAL_ROTATION;

}

void Board::removeFilledRows(int rowStart) {
	// Copy all unfilled rows from rowStart to currentHeight to an unfilled row
	for (int currRow = rowStart, srcRow = rowStart; srcRow <= currentHeight;) {
		if (this->blocksPerRow[srcRow] == BOARD::ROW_SIZE) {
			++srcRow; // Skip this row as it is full and should not be in the result
		}
		else {
			// copy srcRow to currRow
			int currCell = currRow * BOARD::ROW_SIZE, currCellEnd = currRow + BOARD::ROW_SIZE,
				srcCell = srcRow * BOARD::ROW_SIZE, srcCellEnd = srcCell + BOARD::ROW_SIZE;

			for (; currCell < currCellEnd; ++currCell, ++srcCell) {
				this->board[currCell] = this->board[srcCell];
			}

			++currRow, ++srcRow;
		}
	}
}

void Board::setPiece() {
	this->currentHeight = std::max({ getPieceRow(0), getPieceRow(1), getPieceRow(2), getPieceRow(3) });

	this->board[getPieceRowCol(0)] = this->currentPiece->color;
	++this->blocksPerRow[getPieceRow(0)];

	this->board[getPieceRowCol(1)] = this->currentPiece->color;
	++this->blocksPerRow[getPieceRow(1)];

	this->board[getPieceRowCol(2)] = this->currentPiece->color;
	++this->blocksPerRow[getPieceRow(2)];

	this->board[getPieceRowCol(3)] = this->currentPiece->color;
	++this->blocksPerRow[getPieceRow(3)];
}

bool Board::movePieceDown() {
	if (checkOutOfBoundsBelow(PIECES::MOVE_DOWN))
		return false;

	bool canFall = !checkPieceOverlaps(0, PIECES::MOVE_DOWN);

	this->absPiecePositionRow += canFall * PIECES::MOVE_DOWN;

	return canFall;
}

bool Board::movePieceLeft() {
	if (checkOutOfBoundsLeft(PIECES::MOVE_LEFT)) {
		return false;
	}

	bool canMove = !checkPieceOverlaps(PIECES::MOVE_LEFT, 0);

	this->absPiecePositionCol += canMove * PIECES::MOVE_LEFT;
	
	return canMove;
}

bool Board::movePieceRight() {
	if (checkOutOfBoundsRight(PIECES::MOVE_RIGHT))
		return false;

	bool canMove = !checkPieceOverlaps(PIECES::MOVE_RIGHT, 0);

	this->absPiecePositionCol += canMove * PIECES::MOVE_RIGHT;

	return canMove;
};

bool Board::rotatePiece() {
	int oldRotation = this->rotation, oldPositionX = this->absPiecePositionCol, oldPositionY = this->absPiecePositionRow;
	this->rotation = (this->rotation + 1) % PIECES::ROTATION_STATES;
	this->absPiecePositionRow += PIECES::MOVE_UP * checkOutOfBoundsBelow(0) + PIECES::MOVE_UP * checkOutOfBoundsBelow(PIECES::MOVE_UP);
	this->absPiecePositionCol += PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(0) + PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(PIECES::MOVE_RIGHT);
	this->absPiecePositionCol += PIECES::MOVE_LEFT * checkOutOfBoundsRight(0) + PIECES::MOVE_LEFT * checkOutOfBoundsRight(PIECES::MOVE_LEFT);

	if (!checkPieceOverlaps(0, 0)) {}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP)) {
		this->absPiecePositionRow += PIECES::MOVE_UP;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT, 0) && !checkOutOfBoundsRight(PIECES::MOVE_RIGHT)) {
		this->absPiecePositionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT, 0) && !checkOutOfBoundsLeft(PIECES::MOVE_LEFT)) {
		this->absPiecePositionCol += PIECES::MOVE_LEFT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT, PIECES::MOVE_UP) && !checkOutOfBoundsRight(PIECES::MOVE_RIGHT)) {
		this->absPiecePositionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT, PIECES::MOVE_UP) && !checkOutOfBoundsLeft(PIECES::MOVE_LEFT)) {
		this->absPiecePositionCol += PIECES::MOVE_LEFT;
	}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP * 2)) {
		this->absPiecePositionRow += PIECES::MOVE_UP * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT * 2, 0) && !checkOutOfBoundsRight(PIECES::MOVE_RIGHT * 2)) {
		this->absPiecePositionCol += PIECES::MOVE_RIGHT * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT * 2, 0) && !checkOutOfBoundsLeft(PIECES::MOVE_LEFT * 2)) {
		this->absPiecePositionCol += PIECES::MOVE_LEFT * 2;
	}
	else {
		this->rotation = oldRotation;
		this->absPiecePositionCol = oldPositionX;
		this->absPiecePositionRow = oldPositionY;
		return false;
	}
	return true;
};

void Board::dropPiece() {
	while (movePieceDown());
};

