#pragma once

#include <vector>
#include "constants.h"

class Piece {
public:
    int color;
    // position of pieces relative to position of piece given in board
    const std::vector<int>* relXPositions;
    const std::vector<int>* relYPositions;

    Piece();

    virtual ~Piece() {}
};


class Square : public Piece {
public:
    // position of pieces relative to position of piece given in board

    Square();
};

class TBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    TBlock();
};

class LBlockL : public Piece {
public:
    // position of pieces relative to position of piece given in board

    LBlockL();
};

class LBlockR : public Piece {
public:
    // position of pieces relative to position of piece given in board

    LBlockR();
};

// TODO
class Straight : public Piece {
public:
    // position of pieces relative to position of piece given in board

    Straight();
};

class ZBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    ZBlock();
};

class SBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board

    SBlock();
};