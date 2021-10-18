#ifndef Piece_Class_H
#define Piece_Class_H

#include <algorithm>
#include "board.h"

class Piece {
public:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    static Board board;
};

class Square : public Piece {
    int pos;

    Square();

    void rotate();

    void down();

    void left();

    void right();

    void drop();

    void set();
};

class TBlock : public Piece {
    int blocks[4];

    TBlock();

    void rotate();

    void down();

    void left();

    void right();

    void drop();

    void set();
};

class LBlockL : public Piece {
    int blocks[4];
    int offset;
    static const int stateChange[12]; // position of pieces relative to centre piece

    LBlockL();

    void rotate();

    void down();



    void drop();

    void set();
};

class LBlockR : public Piece {
    int blocks[4];
    int offset;
    static const int stateChange[12]; // position of pieces relative to centre piece block[0]

    LBlockR();

    void rotate();

    void down();

    void drop();

    void draw();

    void set();
};

// TODO
//class StraightBlock : public Piece {
//    int blocks[4];
//    int state = 0;
//    int stateChange[4][4];
//    
//    StraightBlock();
//    
//    void rotate();
//
//    void down();
//    
//    void drop();
//
//    void draw();
//
//    void set();
//};

#endif