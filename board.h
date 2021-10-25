#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "pieces.h"
#include "constants.h"

struct indices {
    std::size_t i, j;
};

template <typename T>
Piece* Create() { return new T(); }

typedef Piece* (*CreateFn)();


class Board {
private:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<int> board;
    std::vector<int> blocksPerRow;
    static const std::vector<CreateFn> pieceNames;
    Piece* currentPiece;
    int absPiecePositionX;
    int absPiecePositionY;
    int rotation;
    int currentHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void generateNewPiece();

    inline int get_x(int i) {
        return absPiecePositionX + currentPiece->relXPositions[rotation + i];
    }

    inline int get_y(int i) {
        return absPiecePositionY + currentPiece->relYPositions[rotation + i];
    }

    inline int get_xy(int i) {
        return absPiecePositionX + 10 * absPiecePositionY + currentPiece->relXPositions[rotation + i] + 10 * currentPiece->relYPositions[rotation + i];
    }

    inline bool checkPieceOverlaps(int offsetX, int offsetY) {
        return (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            | (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            | (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            | (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0);
    }

    inline bool checkOutOfBoundsRight(int offsetX) {
        return (get_x(0) + offsetX > BOARD::RIGHT_BOUNDARY) | (get_x(1) + offsetX  > BOARD::RIGHT_BOUNDARY) | (get_x(2) + offsetX > BOARD::RIGHT_BOUNDARY) | (get_x(3) + offsetX > BOARD::RIGHT_BOUNDARY);
    }

    inline bool checkOutOfBoundsLeft(int offsetX) {
        return (get_x(0) + offsetX < BOARD::LEFT_BOUNDARY) | (get_x(1) + offsetX < BOARD::LEFT_BOUNDARY) | (get_x(2) + offsetX < BOARD::LEFT_BOUNDARY) | (get_x(3) + offsetX < BOARD::LEFT_BOUNDARY);
    }

    inline bool checkOutOfBoundsBelow(int offsetY) {
        return (get_y(0) + offsetY < BOARD::BOTTOM_BOUNDARY) | (get_y(1) + offsetY < BOARD::BOTTOM_BOUNDARY) | (get_y(2) + offsetY < BOARD::BOTTOM_BOUNDARY) | (get_y(3) + offsetY < BOARD::BOTTOM_BOUNDARY);
    }

    void removeRows(int rowStart); // remove filled rows

    void setPiece();

    bool movePieceDown();

    bool movePieceLeft();

    bool movePieceRight();

    bool pieceRotate();

    void pieceDrop();

    ~Board() { delete currentPiece; }
};