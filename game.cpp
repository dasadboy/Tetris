#include "game.h"
#include <vector>
#include <initializer_list>


Board::Board() {
	board = std::vector<int>(400, 0);
	offset = 0;
}

int& Board::get(int rowCol) {
	return board[rowCol];
}

int& Board::get(int row, int col) {
	return board[(row * 10) + col];
}

void Board::removeRows(std::initializer_list<int> rows) {
	auto it = begin(rows);
	int src = 10 * ( *it + 1 ), target = *it * 10;
	++it;
	for (auto e = end(rows); it != e; ++it) {
		while (src < *it * 10) {
			board[target++] = board[src++];
		}
		src += 10;
	}
	// replace rows until we encounter an empty row
	bool blockExists = true;
	while (blockExists) {
		blockExists = false;
		while (src % 10) {
			blockExists &= board[target];
			board[target++] = board[src++];
		}
	}
}