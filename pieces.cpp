#include <algorithm>
#include "pieces.h"

using namespace std;

Square::Square() {
    pos = 205;
}

void Square::rotate() {
    // rotating results in the same shape
    return;
}



// TBlock
TBlock::TBlock() {
    blocks[0] = 205;
    blocks[1] = 204;
    blocks[2] = 215;
    blocks[3] = 206;
}

void TBlock::rotate() {
    // blocks[0] is the center that 1, 2, and 3 rotate around;
    blocks[1] = blocks[2];
    blocks[2] = blocks[3];
    // place blocks[3] opposite to blocks[1] from blocks[0]
    blocks[3] = blocks[0] + (blocks[0] - blocks[1]);
    while (blocks[1] >= 0 || blocks[2] >= 0 || blocks[3] >= 0 || board[blocks[0]] || board[blocks[1]] || board[blocks[2]] || board[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
    }
}


// LBlockL

const int LBlockL::stateChange[12] = { -1, 1, -9, 10, -10, -11, 1, -1, 9, -10, 10, 11 };

LBlockL::LBlockL() {
    offset = 3;
    blocks[0] = 215;
    blocks[1] = 214;
    blocks[2] = 216;
    blocks[3] = 206;
}

void LBlockL::rotate() {
    // use stateChange to determine positions of blocks when rotated
    blocks[1] = blocks[0] + stateChange[offset++];
    blocks[2] = blocks[0] + stateChange[offset++];
    blocks[3] = blocks[0] + stateChange[offset++];
    offset %= 12;
}


// LBlockR

const int LBlockR::stateChange[12] = { -1, 1, 11, 10, -10, -9, 1, -1, -11, -10, 10, 9 };

LBlockR::LBlockR() {
    offset = 3;
    blocks[0] = 204;
    blocks[1] = 205;
    blocks[2] = 206;
    blocks[3] = 216;
}

void LBlockR::rotate() {
    // use stateChange to determine positions of blocks when rotated
    blocks[1] = blocks[0] + stateChange[offset++];
    blocks[2] = blocks[0] + stateChange[offset++];
    blocks[3] = blocks[0] + stateChange[offset++];
    ++offset;
    offset %= 12;
}