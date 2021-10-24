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
	currentPiece = pieceNames[rand() % PIECES::NUMBER_OF_PIECES]();
	absPiecePositionX = PIECES::INITIAL_ABS_POSITION_X;
	absPiecePositionY = PIECES::INITIAL_ABS_POSITION_Y;
	rotation = PIECES::INITIAL_ROTATION;
}

void Board::removeRows(int rowStart) {
	for (int curr = rowStart, src = rowStart; src < currentHeight;) {
		if (blocksPerRow[src] == 10) {
			++src;
		}
		else {
			blocksPerRow[curr] = blocksPerRow[src];
			for (int curr_i = curr * 10, src_i = src *10, curr_e = curr_i + 10, src_e = src_i + 10;
				curr_i < curr_e;
				++curr_i) {
				board[curr_i] = board[src_i];
			}
			++curr, ++src;
		}
	}
}

void Board::setPiece() {
	currentHeight = std::max({ get_y(0), get_y(1), get_y(2), get_y(3) });

	board[get_xy(0)] = currentPiece->color;
	++blocksPerRow[get_y(0)];

	board[get_xy(1)] = currentPiece->color;
	++blocksPerRow[get_y(1)];

	board[get_xy(2)] = currentPiece->color;
	++blocksPerRow[get_xy(2)];

	board[get_xy(3)] = currentPiece->color;
	++blocksPerRow[get_xy(3)];
}

bool Board::movePieceDown() {
	bool canFall = !checkOutOfBoundsBelow(-1) && !checkPieceOverlaps(0, -1);

	absPiecePositionY += canFall * -1;

	if (!canFall) setPiece();

	return canFall;
}

bool Board::movePieceLeft() {
	bool canMove = !checkOutOfBoundsLeft(-1) && !checkPieceOverlaps(PIECES::MOVE_LEFT, 0);

	absPiecePositionX += canMove * -1;
	
	return canMove;
}

bool Board::movePieceRight() {
	bool canMove = !checkOutOfBoundsRight(1) && !checkPieceOverlaps(PIECES::MOVE_RIGHT, 0);

	absPiecePositionX += canMove * 1;

	return canMove;
};

bool Board::pieceRotate() {
	int oldRotation = rotation, oldPositionX = absPiecePositionX, oldPositionY = absPiecePositionY;
	rotation = (rotation + 4) % currentPiece->relXPositions.size();
	absPiecePositionY += PIECES::MOVE_UP * checkOutOfBoundsBelow(0) + PIECES::MOVE_UP * checkOutOfBoundsBelow(PIECES::MOVE_UP);
	absPiecePositionX += PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(0) + PIECES::MOVE_RIGHT * checkOutOfBoundsLeft(PIECES::MOVE_RIGHT);
	absPiecePositionX += PIECES::MOVE_LEFT * checkOutOfBoundsRight(0) + PIECES::MOVE_LEFT * checkOutOfBoundsRight(PIECES::MOVE_LEFT);

	if (!checkPieceOverlaps(0, 0)) {}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP)) {
		absPiecePositionY += PIECES::MOVE_UP;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT, 0) && !checkOutOfBoundsRight(1)) {
		absPiecePositionX += PIECES::MOVE_RIGHT;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT, 0) && !checkOutOfBoundsLeft(-1)) {
		absPiecePositionX += PIECES::MOVE_LEFT;
	}
	else if (!checkPieceOverlaps(0, PIECES::MOVE_UP * 2)) {
		absPiecePositionY += PIECES::MOVE_UP * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_RIGHT * 2, 0) && !checkOutOfBoundsRight(PIECES::MOVE_RIGHT * 2)) {
		absPiecePositionX += PIECES::MOVE_RIGHT * 2;
	}
	else if (!checkPieceOverlaps(PIECES::MOVE_LEFT * 2, 0) && !checkOutOfBoundsLeft(PIECES::MOVE_LEFT * 2)) {
		absPiecePositionX += PIECES::MOVE_LEFT * 2;
	}
	else {
		rotation = oldRotation;
		absPiecePositionX = oldPositionX;
		absPiecePositionY = oldPositionY;
		return false;
	}
	return true;
};

void Board::pieceDrop() {
	while (movePieceDown());
};

