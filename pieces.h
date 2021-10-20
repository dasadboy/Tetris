#ifndef Piece_Class_H
#define Piece_Class_H

#include <algorithm>
#include <vector>

class Piece {
public:
    int refpoint = 205;
    int offset;
    int color;
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    virtual void rotate() {};

    virtual ~Piece() {}
};

class Square : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    Square();

    void rotate();
};

class TBlock : public Piece {
public: 
    // position of pieces relative to refpoint
    static const std::vector<int> state_x; 
    static const std::vector<int> state_y;

    TBlock();

    void rotate();
};

class LBlockL : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    LBlockL();

    void rotate();
};

class LBlockR : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    LBlockR();

    void rotate();
};

// TODO
class Straight : public Piece {};

class ZBlock : public Piece {};

class SBlock : public Piece {};

#endif