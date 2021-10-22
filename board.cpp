#include <vector>
#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	board = std::vector<int>(400, 0);
	blocksPerRow = std::vector<int>(40, 0);
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
	currentPiece = pieceNames[rand() % 4]();
	positionOfPiece = 205;
	rotation = 0;
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

void Board::set() {
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

bool Board::pieceDown() {
	bool canFall = !checkBlockedDown() && !checkOverlap(-10);

	positionOfPiece -= 10;

	if (!canFall) set();

	return canFall;
}

void Board::pieceLeft() {
	bool canMove = !checkOverlap(-1) && !checkBlockedLeft();

	positionOfPiece -= canMove;
}

void Board::pieceRight() {
	bool canMove = !checkBlockedRight() && !checkOverlap(1);

	positionOfPiece += canMove;
};

void Board::pieceRotate() {
	rotation = (rotation + 4) % currentPiece->relXPositions.size();
};

void Board::pieceDrop() {
	while (pieceDown());
};

