#include <vector>
#include "board.h"
#include "constants_and_variables.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	board = std::vector<int>(BOARD_SIZE, 0);
	blocksPerRow = std::vector<int>(COLUMN_SIZE, 0);
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
	currentPiece = pieceNames[rand() % NUMBER_OF_PIECES]();
	absPiecePositionX = INITIAL_ABS_POSITIONX;
	absPiecePositionY = INITIAL_ABS_POSITIONY;
	rotation = INITIAL_ROTATION;
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
	bool canMove = !checkOutOfBoundsLeft(-1) && !checkPieceOverlaps(-1, 0);

	absPiecePositionX += canMove * -1;
}

bool Board::movePieceRight() {
	bool canMove = !checkOutOfBoundsRight(1) && !checkPieceOverlaps(1, 0);

	absPiecePositionX += canMove * 1;
};

bool Board::pieceRotate() {
	int oldRotation = rotation, oldPositionX = absPiecePositionX, oldPositionY = absPiecePositionY;
	rotation = (rotation + 4) % currentPiece->relXPositions.size();
	absPiecePositionY += UP_ONE_ROW * checkOutOfBoundsBelow(0) + UP_ONE_ROW * checkOutOfBoundsBelow(1);
	absPiecePositionX += RIGHT_ONE_COLUMN * checkOutOfBoundsLeft(0) + RIGHT_ONE_COLUMN * checkOutOfBoundsLeft(1);
	absPiecePositionX += LEFT_ONE_COLUMN * checkOutOfBoundsRight(0) + LEFT_ONE_COLUMN * checkOutOfBoundsRight(-1);

	if (!checkPieceOverlaps(0, 0)) {}
	else if (!checkPieceOverlaps(0, 1)) {
		absPiecePositionY += 1;
	}
	else if (!checkPieceOverlaps(1, 0) && !checkOutOfBoundsRight(1)) {
		absPiecePositionX += 1;
	}
	else if (!checkPieceOverlaps(-1, 0) && !checkOutOfBoundsLeft(-1)) {
		absPiecePositionX += -1;
	}
	else if (!checkPieceOverlaps(0, 2)) {
		absPiecePositionY += 2;
	}
	else if (!checkPieceOverlaps(2, 0) && !checkOutOfBoundsRight(2)) {
		absPiecePositionX += 2;
	}
	else if (!checkPieceOverlaps(-2, 0) && !checkOutOfBoundsLeft(-2)) {
		absPiecePositionX += -2;
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

