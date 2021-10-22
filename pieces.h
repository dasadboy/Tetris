#pragma once

#include <vector>

class Piece {
public:
    int color;
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;

    virtual ~Piece() {}
};

class Square : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    Square();
};

class TBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions; 
    static const std::vector<int> relYPositions;
    TBlock();
};

class LBlockL : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    LBlockL();
};

class LBlockR : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    LBlockR();
};

// TODO
class Straight : public Piece {

public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    Straight();
};

class ZBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    ZBlock();
};

class SBlock : public Piece {
public:
    // position of pieces relative to position of piece given in board
    static const std::vector<int> relXPositions;
    static const std::vector<int> relYPositions;
    SBlock();
};