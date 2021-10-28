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
public:
    Piece* currentPiece;
    int absPiecePositionRow;
    int absPiecePositionCol;
    int rotation;
    int currentHeight;


    Board();

    Board(Piece& piece);

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void generateNewPiece();

    void generateNewPiece(Piece& piece);

    inline int get_x(int i) {
        return this->absPiecePositionRow + this->currentPiece->relXPositions[rotation + i];
    }

    inline int get_y(int i) {
        return this->absPiecePositionCol + this->currentPiece->relYPositions[rotation + i];
    }

    inline int get_xy(int i) {
        return this->absPiecePositionRow + 10 * this->absPiecePositionCol + this->currentPiece->relXPositions[this->rotation + i] + 10 * this->currentPiece->relYPositions[this->rotation + i];
    }

    inline bool checkPieceOverlaps(int offsetX, int offsetY) {
        return (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            || (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            || (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0)
            || (board[((get_xy(0) + offsetX + BOARD::ROW_SIZE * offsetY + BOARD::BOARD_SIZE) % BOARD::BOARD_SIZE)] != 0);
    }

    inline bool checkOutOfBoundsRight(int offsetX) {
        return (get_x(0) + offsetX > BOARD::RIGHT_BOUNDARY) || (get_x(1) + offsetX  > BOARD::RIGHT_BOUNDARY) || (get_x(2) + offsetX > BOARD::RIGHT_BOUNDARY) || (get_x(3) + offsetX > BOARD::RIGHT_BOUNDARY);
    }

    inline bool checkOutOfBoundsLeft(int offsetX) {
        return (get_x(0) + offsetX < BOARD::LEFT_BOUNDARY) || (get_x(1) + offsetX < BOARD::LEFT_BOUNDARY) || (get_x(2) + offsetX < BOARD::LEFT_BOUNDARY) || (get_x(3) + offsetX < BOARD::LEFT_BOUNDARY);
    }

    inline bool checkOutOfBoundsBelow(int offsetY) {
        return (get_y(0) + offsetY <= BOARD::BOTTOM_BOUNDARY) || (get_y(1) + offsetY <= BOARD::BOTTOM_BOUNDARY) || (get_y(2) + offsetY <= BOARD::BOTTOM_BOUNDARY) || (get_y(3) + offsetY <= BOARD::BOTTOM_BOUNDARY);
    }

    void removeFilledRows(int rowStart); // remove filled rows

    void setPiece();

    bool movePieceDown();

    bool movePieceLeft();

    bool movePieceRight();

    bool rotatePiece();

    void dropPiece();

    ~Board() { delete currentPiece; }
};