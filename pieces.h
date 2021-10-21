#ifndef Piece_Class_H
#define Piece_Class_H

#include <algorithm>
#include <vector>

class Piece {
public:
    int color;
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;

    virtual ~Piece() {}
};

class Square : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
};

class TBlock : public Piece {
public: 
    // position of pieces relative to refpoint
    static const std::vector<int> state_x; 
    static const std::vector<int> state_y;
};

class LBlockL : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
};

class LBlockR : public Piece {
public:
    // position of pieces relative to refpoint
    static const std::vector<int> state_x;
    static const std::vector<int> state_y;
};

// TODO
class Straight : public Piece {};

class ZBlock : public Piece {};

class SBlock : public Piece {};

#endif