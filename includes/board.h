#pragma once

#include "blocks.h"

class Board {
    
    // private data types
    struct indices {
        int i, j;
    };

    struct BoardCell {
        static const Block defaultBlock;
        Block block;
        bool isOccupied;
        BoardCell() {
            isOccupied = false;
        }
        BoardCell(Block& b, bool occupied) : block(b), isOccupied(occupied) {}
        void operator=(const BoardCell& src) {
            Block newBlock = src.block;
            sf::Vector2f currPosition = this->block.getPos();
            newBlock.setPos(currPosition);
            this->isOccupied = src.isOccupied;
            this->block = newBlock;
        }
    };

    // private member variables
    std::vector<BoardCell> board;
    std::vector<int> blocksPerRow;

public:

    Board();

    BoardCell& operator[](int rowCol);

    BoardCell& operator[](indices rowCol); // called with board({row, col}) or given object 'obj' of type indices, board(obj)

    bool checkPositionLegal(int row, int col);

    int removeFilledRows(int rowStart); // remove filled rows

    int setPiece(std::vector<int>& rows, std::vector<int>& cols, std::vector<Block>& blocks);

    void draw(sf::RenderWindow& window);

    bool checkGameOver();
};