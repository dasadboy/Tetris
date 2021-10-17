#include "game.h"
#include <vector>
#include <initializer_list>


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
