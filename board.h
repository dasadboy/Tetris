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

    void removeRows(int rowStart); // remove filled rows

    void set();

    bool pieceDown();

    void pieceLeft();

    void pieceRight();

    void pieceRotate();

    void pieceDrop();

    ~Board() {
        delete currPiece;
    }
};

#endif