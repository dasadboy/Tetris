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
    std::vector<int>* currPiecePos;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    inline bool checkOverlap(int offset) {
        return (board[(*currPiecePos)[0] + offset] != 0)
            & (board[(*currPiecePos)[1] + offset] != 0)
            & (board[(*currPiecePos)[2] + offset] != 0)
            & (board[(*currPiecePos)[3] + offset] != 0);
    }

    inline bool checkBlockedRight() {
        return ((*currPiecePos)[0] % 10 == 9)
            & ((*currPiecePos)[1] % 10 == 9)
            & ((*currPiecePos)[2] % 10 == 9)
            & ((*currPiecePos)[3] % 10 == 9);
    }

    inline bool checkBlockedLeft() {
        return ((*currPiecePos)[0] % 10 == 0)
            & ((*currPiecePos)[1] % 10 == 0)
            & ((*currPiecePos)[2] % 10 == 0)
            & ((*currPiecePos)[3] % 10 == 0);
    }

    inline bool checkBlockedDown() {
        return ((*currPiecePos)[0] - 10 < 0)
            & ((*currPiecePos)[1] - 10 < 0)
            & ((*currPiecePos)[2] - 10 < 0)
            & ((*currPiecePos)[3] - 10 < 0);
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