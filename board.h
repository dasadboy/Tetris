#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "pieces.h"

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
    int positionOfPiece;
    int rotation;
    int currentHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void generateNewPiece();

    inline int get_x(int i) {
        return (positionOfPiece % 10) + currentPiece->relXPositions[rotation + i];
    }

    inline int get_y(int i) {
        return (positionOfPiece / 10) + currentPiece->relYPositions[rotation + i];
    }

    inline int get_xy(int i) {
        return positionOfPiece + currentPiece->relXPositions[rotation + i] + 10 * currentPiece->relYPositions[rotation + i];
    }

    inline bool checkPieceOverlaps(int offset) {
        return (board[((get_xy(0) + offset + 400) % 400)] != 0) | (board[((get_xy(1) + offset + 400) % 400)] != 0) | (board[((get_xy(2) + offset + 400) % 400)] != 0) | (board[((get_xy(3) + offset + 400) % 400)] != 0);
    }

    inline bool checkOutOfBoundsRight(int offset) {
        return (get_x(0) + offset % 10 > 9) | (get_x(1) + offset % 10 > 9) | (get_x(2) + offset % 10 > 9) | (get_x(3) + offset % 10 > 9);
    }

    inline bool checkOutOfBoundsLeft(int offset) {
        return (get_x(0) + offset % 10 < 0) | (get_x(1) + offset % 10 < 0) | (get_x(2) + offset % 10 < 0) | (get_x(3) + offset % 10 < 0);
    }

    inline bool checkOutOfBoundsBelow(int offset) {
        return (get_y(0) + offset / 10 < 0) | (get_y(1) + offset / 10 < 0) | (get_y(2) + offset / 10 < 0) | (get_y(3) + offset % 10 < 0);
    }

    void removeRows(int rowStart); // remove filled rows

    void setPiece();

    bool movePieceDown();

    void movePieceLeft();

    void movePieceRight();

    void pieceRotate();

    void pieceDrop();

    ~Board() { delete currentPiece; }
};