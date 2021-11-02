#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "pieces.h"
#include "constants.h"

struct indices {
    int i, j;
};

template <typename T>
Piece* Create() { return new T(); }


typedef Piece* (*CreateFn)();


class Board {
public:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<int> board;
    std::vector<int> blocksPerRow;
    static const std::vector<CreateFn> pieceNames;
    Piece* currentPiece;
    int absPiecePositionRow;
    int absPiecePositionCol;
    int rotation;
    int currentHeight;


    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void generateNewPiece();

    void generateNewPiece(Piece* piece);

    inline int getPieceCol(int i);

    inline int getPieceRow(int i);

    inline int getPieceRowCol(int i);

    inline bool checkPieceOverlaps(int offsetX, int offsetY);

    inline bool checkOutOfBoundsRight(int offsetX);

    inline bool checkOutOfBoundsLeft(int offsetX);

    inline bool checkOutOfBoundsBelow(int offsetY);

    void removeFilledRows(int rowStart); // remove filled rows

    void setPiece();

    bool movePieceDown();

    bool movePieceLeft();

    bool movePieceRight();

    bool rotatePiece();

    void dropPiece();

    ~Board() { delete currentPiece; }
};