#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "blocks.h"

struct indices {
    int i, j;
};


class Board {
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<int> board;
    std::vector<int> blocksPerRow;
    int currentHeight;
public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col}) or given object 'obj' of type indices, board(obj)

    bool checkPositionLegal(int row, int col);

    void removeFilledRows(int rowStart); // remove filled rows

    void setPiece(std::vector<int> rows, std::vector<int> cols, int color);

    void drawBlock(int row, int col);

    void draw();
};