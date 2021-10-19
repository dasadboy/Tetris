#ifndef Piece_Class_H
#define Piece_Class_H

#include <algorithm>
#include <vector>

class Piece {
public:
    std::vector<int> pos;
    int color;

    void rotate();
};

class Square : public Piece {
public:
    std::vector<int> pos;

    Square();

    void rotate();
};

class TBlock : public Piece {
public:
    std::vector<int> pos;

    TBlock();

    void rotate();
};

class LBlockL : public Piece {
public:
    std::vector<int> pos;
    int offset;
    static const int stateChange[12]; // position of pieces relative to centre piece

    LBlockL();

    void rotate();
};

class LBlockR : public Piece {
public:
    std::vector<int> pos;
    int offset;
    static const int stateChange[12]; // position of pieces relative to centre piece block[0]

    LBlockR();

    void rotate();
};

// TODO
class Straight : public Piece {};

class ZBlock : public Piece {};

class SBlock : public Piece {};

#endif