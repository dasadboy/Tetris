#ifndef Board_Class_H
#define Board_Class_H

#include <iostream>
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
    std::vector<int> rowPop;
    static const std::vector<CreateFn> pieceNames;
    Piece* currPiece;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    inline bool checkOverlap(int dir) {
        return (board[currPiece->refpoint + currPiece->state_x[currPiece->offset] + 10 * currPiece->state_y[currPiece->offset]] != 0)
            | (board[currPiece->refpoint + currPiece->state_x[currPiece->offset + 1] + 10 * currPiece->state_y[currPiece->offset + 1]] != 0)
            | (board[currPiece->refpoint + currPiece->state_x[currPiece->offset + 2] + 10 * currPiece->state_y[currPiece->offset + 2]] != 0)
            | (board[currPiece->refpoint + currPiece->state_x[currPiece->offset + 3] + 10 * currPiece->state_y[currPiece->offset + 3]] != 0);
    }

    inline bool checkBlockedRight() {
        return (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset] == 9
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 1] == 9
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 2] == 9
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 3] == 9;
    }

    inline bool checkBlockedLeft() {
        return (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset] == 0
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 1] == 0
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 2] == 0
            | (currPiece->refpoint % 10) + currPiece->state_x[currPiece->offset + 3] == 0;
    }

    inline bool checkBlockedDown() {
        return (currPiece->refpoint % 10) + 10 * currPiece->state_y[currPiece->offset] == 0
            | (currPiece->refpoint % 10) + 10 * currPiece->state_y[currPiece->offset + 1] == 0
            | (currPiece->refpoint % 10) + 10 * currPiece->state_y[currPiece->offset + 2] == 0
            | (currPiece->refpoint % 10) + 10 * currPiece->state_y[currPiece->offset + 3] == 0;
    }

    void removeRows(int rowStart); // remove filled rows

    void set();

    bool pieceDown();

    void pieceLeft();

    void pieceRight();

    void pieceRotate();

    void pieceDrop();

    ~Board() { delete currPiece; }
};

#endif