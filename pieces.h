#pragma once

#include <vector>
#include "constants.h"
#include "board.h"

class Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int>* relRowPositions;
    static const std::vector<int>* relColPositions;
    Board& board;
    int color;
    int positionRow;
    int positionCol;
    int rotation;

    Piece(Board& b);

    virtual inline bool checkCollidesAtOffset(int rowOffset, int colOffset);

    virtual bool moveDown();

    virtual bool moveLeft();

    virtual bool moveRight();

    virtual void drop();

    virtual bool rotate();

    virtual void set();

    virtual ~Piece() {}
};


class Square : public Piece {
public:
    // position of pieces relative to position of piece given in board

    Square(Board& b);

    bool rotate() override;
};

class TBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    TBlock(Board& b);
};

class LBlockL : public Piece {
public:
    // position of pieces relative to position of piece given in board

    LBlockL(Board& b);
};

class LBlockR : public Piece {
public:
    // position of pieces relative to position of piece given in board

    LBlockR(Board& b);
};

// TODO
class Straight : public Piece {
public:
    // position of pieces relative to position of piece given in board

    Straight(Board& b);
};

class ZBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    ZBlock(Board& b);
};

class SBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    SBlock(Board& b);
};