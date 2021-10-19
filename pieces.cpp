#include <algorithm>
#include "pieces.h"

using namespace std;

void Piece::rotate() {}

Square::Square() {
    pos = { 205, 206, 215, 216 };
}

void Square::rotate() {
    // rotating results in the same shape
    return;
}



// TBlock
TBlock::TBlock() {
    pos[0] = 205;
    pos[1] = 204;
    pos[2] = 215;
    pos[3] = 206;
}

void TBlock::rotate() {
    // pos[0] is the center that 1, 2, and 3 rotate around;
    pos[1] = pos[2];
    pos[2] = pos[3];
    // place pos[3] opposite to pos[1] from pos[0]
    pos[3] = pos[0] + (pos[0] - pos[1]);
}


// LBlockL

const int LBlockL::stateChange[12] = { -1, 1, -9, 10, -10, -11, 1, -1, 9, -10, 10, 11 };

LBlockL::LBlockL() {
    offset = 3;
    pos[0] = 215;
    pos[1] = 214;
    pos[2] = 216;
    pos[3] = 206;
}

void LBlockL::rotate() {
    // use stateChange to determine positions of pos when rotated
    pos[1] = pos[0] + stateChange[offset++];
    pos[2] = pos[0] + stateChange[offset++];
    pos[3] = pos[0] + stateChange[offset++];
    offset %= 12;
}


// LBlockR

const int LBlockR::stateChange[12] = { -1, 1, 11, 10, -10, -9, 1, -1, -11, -10, 10, 9 };

LBlockR::LBlockR() {
    offset = 3;
    pos[0] = 204;
    pos[1] = 205;
    pos[2] = 206;
    pos[3] = 216;
}

void LBlockR::rotate() {
    // use stateChange to determine positions of pos when rotated
    pos[1] = pos[0] + stateChange[offset++];
    pos[2] = pos[0] + stateChange[offset++];
    pos[3] = pos[0] + stateChange[offset++];
    ++offset;
    offset %= 12;
}