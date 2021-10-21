#include <vector>
#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock>};

Board::Board() {
	board = std::vector<int>(400, 0);
	rowPop = std::vector<int>(40, 0);
	currHeight = 0;
	currPiece = pieceNames[rand() % 7]();
	refpoint = 205;
	offset = 0;
	std:: cout << currPiece->state_x.size() << std::endl;
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}

int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
}

void Board::newPiece() {
	currPiece = pieceNames[rand() % 4]();
	refpoint = 205;
	offset = 0;
}

void Board::removeRows(int rowStart) {
	for (int curr = rowStart, src = rowStart; src < currHeight;) {
		if (rowPop[src] == 10) {
			++src;
		}
		else {
			rowPop[curr] = rowPop[src];
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
	currHeight = std::max({ get_y(0), get_y(1), get_y(2), get_y(3) });

	board[get_xy(0)] = currPiece->color;
	++rowPop[get_y(0)];

	board[get_xy(1)] = currPiece->color;
	++rowPop[get_y(1)];

	board[get_xy(2)] = currPiece->color;
	++rowPop[get_xy(2)];

	board[get_xy(3)] = currPiece->color;
	++rowPop[get_xy(3)];
}

bool Board::pieceDown() {
	bool canFall = !(checkBlockedDown() | checkOverlap(-10));

	refpoint -= 10;

	if (!canFall) set();

	return canFall;
}

void Board::pieceLeft() {
	bool canMove = !(checkOverlap(-1) | checkBlockedLeft());

	refpoint -= canMove;
}

void Board::pieceRight() {
	bool canMove = !(checkBlockedRight() | checkOverlap(1));

	refpoint += canMove;
};

void Board::pieceRotate() {
	offset = (offset + 4) % currPiece->state_x.size();
};

void Board::pieceDrop() {
	while (pieceDown());
};

