#include "board.h"
#include "pieces.h"


Board::Board() {
	board = std::vector<int>(400, 0);
	rowPop = std::vector<int>(40);
	currHeight = 0;
}

int& Board::operator[] (int rowCol){
	return board[rowCol];
}

int& Board::operator[] (indices rowCol) {
	return board[rowCol.i * 10 + rowCol.j];
}

void Board::removeRows(int rowStart) {
	for (int curr = rowStart * 10, src = rowStart; src < currHeight;) {
		if (rowPop[src / 10] == 10) {
			src += 10;
		}
		else {
			rowPop[curr / 10] = rowPop[src / 10];
			board[curr++] = board[src++];
			while (curr % 10) {
				board[curr++] = board[src++];
			}
		}
	}
}

void Board::set(int b0, int b1, int b2, int b3, int color) {
	board[b0] = color;
	++rowPop[b0];
	board[b1] = color;
	++rowPop[b1];
	board[b2] = color;
	++rowPop[b2];
	board[b3] = color;
	++rowPop[b3];
}
