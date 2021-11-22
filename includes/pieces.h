#pragma once

#include <vector>
#include "board.h"

class Piece {
public:
    // position of pieces relative to position of piece given in board
    Board& board;
    int positionRow;
    int positionCol;
    int rotation;
    std::vector<Block> blocks;

    Piece(Board& b);

    virtual int getBlockPositionRow(int blockNumber) = 0;

    virtual int getBlockPositionCol(int blockNumber) = 0;

    virtual sf::Color getBlockColor() = 0;

    virtual bool checkCollidesAtOffset(int rowOffset, int colOffset);

    // moves piece down, returns false if it could not move down
    virtual bool moveDown();

    // moves piece left, returns false if it could not
    virtual bool moveLeft();

    // moves piece right, returns false if it could not
    virtual bool moveRight();

    // moves piece down until it cannot
    virtual void drop();

    // rotates piece clockwise, returns false if it cannot turn
    virtual bool rotate();

    virtual void updateBlocks();

    // sets piece on board
    virtual void set();

    // draws piece to screen
    virtual void draw();

    // del
    virtual ~Piece() {}
};

template <class P>
class PieceHolder : public Piece {
    static const std::vector<int> relRowPositions;
    static const std::vector<int> relColPositions;
    static const sf::Color color;
public:
    PieceHolder(Board& b);

    virtual int getBlockPositionRow(int blockNumber) {
        return this->positionRow + relRowPositions[this->rotation * PIECES::STATES_OF_ROTATION + blockNumber];
    }

    virtual int getBlockPositionCol(int blockNumber) {
        return this->positionCol + relColPositions[this->rotation * PIECES::STATES_OF_ROTATION + blockNumber];
    }

    virtual sf::Color getBlockColor() {
        return this->color;
    }
};


class Square : public PieceHolder<Square> {
public:
    // position of pieces relative to position of piece given in board

    Square(Board& b);

    bool rotate() override;
};

class TBlock : public PieceHolder<TBlock> {
public:
    // position of pieces relative to position of piece given in board

    TBlock(Board& b);
};

class LBlockL : public PieceHolder<LBlockL> {
public:
    // position of pieces relative to position of piece given in board

    LBlockL(Board& b);
};

class LBlockR : public PieceHolder<LBlockR> {
public:
    // position of pieces relative to position of piece given in board

    LBlockR(Board& b);
};

// TODO
class Straight : public PieceHolder<Straight> {
public:
    // position of pieces relative to position of piece given in board

    Straight(Board& b);
};

class ZBlock : public PieceHolder<ZBlock> {
public:
    // position of pieces relative to position of piece given in board

    ZBlock(Board& b);
};

class SBlock : public PieceHolder<SBlock> {
public:
    // position of pieces relative to position of piece given in board

    SBlock(Board& b);
};