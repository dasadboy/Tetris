#ifndef Piece_Class_H
#define Piece_Class_H

#include <algorithm>

using namespace std;


class Piece {
public:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    static bool* board[400];
};

class Square : public Piece {
    int pos;

    Square();

    void rotate();

    void down();

    void drop();

    void draw();

    void set();
};

class TBlock : public Piece {
    int blocks[4];

    TBlock();

    void rotate();

    void down();

    void drop();

    void draw();

    void set();
};

class LBlockL : public Piece {
    bool blocks[4] = {};
    int state = 0;
    int stateChange[4][4] = { {11, 0, -11, 2},{-9, 0, 9, -20},{-11, 0, 11, -2},{9, 0, -9, 20} }; // stateChange[i] = modifications needed to go from state i -> (i+1)%4

    LBlockL();

    void rotate();

    void down();

    void drop();

    void draw();

    void set();
};

class LBlockR : public Piece {
    int blocks[4];
    int state = 0;
    int stateChange[4][4] = { {11, 0, -11, -20}, {-9, 0, 9, -2}, {-11, 0, 11, 20}, {9, 0, -9, 2} }; // stateChange[i] = modifications needed to go from state i -> (i+1)%4

    LBlockR();

    void rotate();

    void down();

    void drop();

    void draw();

    void set();
};

class StraightBlock : public Piece {
    int blocks[4];
    int state = 0;
    int stateChange[4][4];
    
    StraightBlock();
    
    void rotate();

    void down();
    
    void drop();

    void draw();

    void set();
};

#endif