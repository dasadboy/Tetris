#ifndef Board_Class_H
#define Board_Class_H

#include <iostream>
#include <vector>
#include "pieces.h"

struct indices {
    std::size_t i, j;
};

class Board {
private:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<int> board;
    std::vector<int> rowPop;
    std::vector<Piece> pieceNames;
    Piece currPiece;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void removeRows(int rowStart); // remove filled rows

    void set(int b0, int b1, int b2, int b3, int color);

    void pieceDown();

    void pieceLeft();

    void pieceRight();

    void pieceRotate();

    void pieceDrop();
};

#endif