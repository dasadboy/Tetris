#include <vector>
#include "board.h"

const std::vector<CreateFn> Board::pieceNames = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock> };

Board::Board() {
	board = std::vector<int>(400, 0);
	rowPop = std::vector<int>(40, 0);
	currPiece = pieceNames[rand()%7]();
	currPiecePos = &(currPiece->pos);
	currHeight = 0;
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}

int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
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
	board[(*currPiecePos)[0]] = currPiece->color;
	++rowPop[(*currPiecePos)[0]];

	board[(*currPiecePos)[1]] = currPiece->color;
	++rowPop[(*currPiecePos)[1]];

	board[(*currPiecePos)[2]] = currPiece->color;
	++rowPop[(*currPiecePos)[2]];

	board[(*currPiecePos)[3]] = currPiece->color;
	++rowPop[(*currPiecePos)[3]];
}

bool Board::pieceDown() {
	bool cantFall = false;

	for (auto it = begin((*currPiecePos)), e = end((*currPiecePos)); it != e; ++it) {
		cantFall &= (board[ (*it) - 10] != 0);
	}

	for (auto it = begin((*currPiecePos)), e = end((*currPiecePos)); it != e; ++it) {
		*it -= (!cantFall)*10;
	}

	if (cantFall) set();

	return cantFall;
}

void Board::pieceLeft() {
	bool cantMove = false;

	for (auto it = begin((*currPiecePos)), e = end((*currPiecePos)); it != e; ++it) {
		cantMove &= (board[ (*it) - 10 ] != 0);
	}

	for (auto it = begin((*currPiecePos)), e = end((*currPiecePos)); it != e; ++it) {
		*it -= (!cantMove) * 10;
	}
}



void Board::pieceRight() {};

void Board::pieceRotate() {};

void Board::pieceDrop() {};

