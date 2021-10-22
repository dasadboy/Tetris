#pragma once

#include <vector>

class Piece {
public:
    int color;
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    virtual ~Piece() {}
};

class Square : public Piece {
public:
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    Square();
};

class TBlock : public Piece {
public: 
    // position of pieces relative to refpoint
    static const std::vector<int> state_x; 
    static const std::vector<int> state_y;
    TBlock();
};

class LBlockL : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    LBlockL();
};

class LBlockR : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    LBlockR();
};

// TODO
class Straight : public Piece {

public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    Straight();
};

class ZBlock : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    ZBlock();
};

class SBlock : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
    SBlock();
};