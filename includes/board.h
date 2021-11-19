#pragma once

#include "blocks.h"
#include <iostream>
#include <algorithm>
#include <vector>

struct indices {
    int i, j;
};

struct BoardCell {
    Block& block;
    bool isOccupied;
    BoardCell(Block& b, bool state = false) : block(b) {
        this->isOccupied = state;
    }
    void setOccupied() {
        this->isOccupied = true;
    }
    void operator=(BoardCell& src) {
        Block newBlock = src.block;
        sf::Vector2f currPosition = this->block.getPos();
        newBlock.setPos(currPosition);
        this->isOccupied = src.isOccupied;
    }
    void reset(int row, int col) {
        bool isOccupied = false;
        block = Block(row, col);
    }
};

class Board {
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<BoardCell> board;
    std::vector<int> blocksPerRow;
    int currentHeight;
public:

    Board();

    BoardCell& operator[](int rowCol);

    BoardCell& operator[](indices rowCol); // called with board({row, col}) or given object 'obj' of type indices, board(obj)

    bool checkPositionLegal(int row, int col);

    void removeFilledRows(int rowStart); // remove filled rows

    void setPiece(std::vector<int> rows, std::vector<int> cols, std::vector<Block> blocks);

    void draw();
};