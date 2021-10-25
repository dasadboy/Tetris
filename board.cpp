#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	board = std::vector<int>(BOARD::BOARD_SIZE, 0);
	blocksPerRow = std::vector<int>(BOARD::COLUMN_SIZE, 0);
	currentHeight = 0;
	generateNewPiece();
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}

int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
}

void Board::generateNewPiece() {
	this->currentPiece = this->pieceNames[rand() % PIECES::NUMBER_OF_PIECES]();
	this->absPiecePositionX = PIECES::INITIAL_ABS_POSITION_X;
	this->absPiecePositionY = PIECES::INITIAL_ABS_POSITION_Y;
	this->rotation = PIECES::INITIAL_ROTATION;
}

void Board::removeRows(int rowStart) {
	for (int curr = rowStart, src = rowStart; src < currentHeight;) {
		if (this->blocksPerRow[src] == BOARD::ROW_SIZE) {
			++src;
		}
		else {
			this->blocksPerRow[curr] = this->blocksPerRow[src];
			for (int curr_i = curr * BOARD::ROW_SIZE, src_i = src * BOARD::ROW_SIZE,
				curr_e = curr_i + BOARD::ROW_SIZE, src_e = src_i + BOARD::ROW_SIZE;
				curr_i < curr_e;
				++curr_i) {
				this->board[curr_i] = this->board[src_i];
			}
			++curr, ++src;
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

	this->absPiecePositionY += canFall * PIECES::MOVE_DOWN;

	if (!canFall) setPiece();

	return canFall;
}

bool Board::movePieceLeft() {
	bool canMove = !checkOutOfBoundsLeft(PIECES::MOVE_LEFT) && !checkPieceOverlaps(PIECES::MOVE_LEFT, 0);

	this->absPiecePositionX += canMove * PIECES::MOVE_LEFT;
	
	return canMove;
}

bool Board::movePieceRight() {
	bool canMove = !checkOutOfBoundsRight(PIECES::MOVE_RIGHT) && !checkPieceOverlaps(PIECES::MOVE_RIGHT, 0);

	this->absPiecePositionX += canMove * PIECES::MOVE_RIGHT;

	return canMove;
};

bool Board::pieceRotate() {
	int oldRotation = this->rotation, oldPositionX = this->absPiecePositionX, oldPositionY = this->absPiecePositionY;
	this->rotation = (this->rotation + 4) % this->currentPiece->relXPositions.size();
	this->absPiecePositionY += PIECES::MOVE_UP * checkOutOfBoundsBelow(0) + PIECES::MOVE_UP * checkOutOfBoundsBelow(PIECES::MOVE_UP);
	this->absPiecePositionX += PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(0) + PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(PIECES::MOVE_RIGHT);
	this->absPiecePositionX += PIECES::MOVE_LEFT * checkOutOfBoundsRight(0) + PIECES::MOVE_LEFT * checkOutOfBoundsRight(PIECES::MOVE_LEFT);

	if (!checkPieceOverlaps(0, 0)) {}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP)) {
		this->absPiecePositionY += PIECES::MOVE_UP;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT, 0) && !checkOutOfBoundsRight(1)) {
		this->absPiecePositionX += PIECES::MOVE_RIGHT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT, 0) && !checkOutOfBoundsLeft(-1)) {
		this->absPiecePositionX += PIECES::MOVE_LEFT;
	}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP * 2)) {
		this->absPiecePositionY += PIECES::MOVE_UP * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT * 2, 0) && !checkOutOfBoundsRight(PIECES::MOVE_RIGHT * 2)) {
		this->absPiecePositionX += PIECES::MOVE_RIGHT * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT * 2, 0) && !checkOutOfBoundsLeft(PIECES::MOVE_LEFT * 2)) {
		this->absPiecePositionX += PIECES::MOVE_LEFT * 2;
	}
	else {
		this->rotation = oldRotation;
		this->absPiecePositionX = oldPositionX;
		this->absPiecePositionY = oldPositionY;
		return false;
	}
	return true;
};

void Board::pieceDrop() {
	while (movePieceDown());
};

