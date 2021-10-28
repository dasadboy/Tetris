#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	board = std::vector<int>(BOARD::BOARD_SIZE, 0);
	blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	currentHeight = 0;
	generateNewPiece();
}

Board::Board(Piece& piece) {
	board = std::vector<int>(BOARD::BOARD_SIZE, 0);
	blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	currentHeight = 0;
	generateNewPiece(piece);
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}

int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
}

void Board::generateNewPiece() {
	this->currentPiece = this->pieceNames[rand() % PIECES::NUMBER_OF_PIECES]();
	this->absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->absPiecePositionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->rotation = PIECES::INITIAL_ROTATION;
}

void Board::generateNewPiece(Piece& piece) {
	this->currentPiece = &piece;
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
	this->currentHeight = std::max({ get_y(0), get_y(1), get_y(2), get_y(3) });

	this->board[get_xy(0)] = this->currentPiece->color;
	++this->blocksPerRow[get_y(0)];

	this->board[get_xy(1)] = this->currentPiece->color;
	++this->blocksPerRow[get_y(1)];

	this->board[get_xy(2)] = this->currentPiece->color;
	++this->blocksPerRow[get_xy(2)];

	this->board[get_xy(3)] = this->currentPiece->color;
	++this->blocksPerRow[get_xy(3)];
}

bool Board::movePieceDown() {
	bool canFall = !checkOutOfBoundsBelow(PIECES::MOVE_DOWN) && !checkPieceOverlaps(0, PIECES::MOVE_DOWN);

	this->absPiecePositionRow += canFall * PIECES::MOVE_DOWN;

	if (!canFall) setPiece();

	return canFall;
}

bool Board::movePieceLeft() {
	bool canMove = !checkOutOfBoundsLeft(PIECES::MOVE_LEFT) && !checkPieceOverlaps(PIECES::MOVE_LEFT, 0);

	this->absPiecePositionCol += canMove * PIECES::MOVE_LEFT;
	
	return canMove;
}

bool Board::movePieceRight() {
	bool canMove = !checkOutOfBoundsRight(PIECES::MOVE_RIGHT) && !checkPieceOverlaps(PIECES::MOVE_RIGHT, 0);

	this->absPiecePositionCol += canMove * PIECES::MOVE_RIGHT;

	return canMove;
};

bool Board::rotatePiece() {
	int oldRotation = this->rotation, oldPositionX = this->absPiecePositionCol, oldPositionY = this->absPiecePositionRow;
	this->rotation = (this->rotation + 4) % this->currentPiece->relXPositions.size();
	this->absPiecePositionRow += PIECES::MOVE_UP * checkOutOfBoundsBelow(0) + PIECES::MOVE_UP * checkOutOfBoundsBelow(PIECES::MOVE_UP);
	this->absPiecePositionCol += PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(0) + PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(PIECES::MOVE_RIGHT);
	this->absPiecePositionCol += PIECES::MOVE_LEFT * checkOutOfBoundsRight(0) + PIECES::MOVE_LEFT * checkOutOfBoundsRight(PIECES::MOVE_LEFT);

	if (!checkPieceOverlaps(0, 0)) {}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP)) {
		this->absPiecePositionRow += PIECES::MOVE_UP;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT, 0) && !checkOutOfBoundsRight(1)) {
		this->absPiecePositionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT, 0) && !checkOutOfBoundsLeft(-1)) {
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

