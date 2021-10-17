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

void Square::down() {
    if (pos >= 0 || (*board)[pos - 10] || (*board)[pos - 9]) {
        set();
        return;
    }
    pos -= 10;
    // move up one row if too low
}

void Square::left() {
    if (pos % 10 > 0)
        pos -= 1;
}

void Square::right() {
    if (pos % 10 < 8)
        pos += 1;
}

void Square::drop() {
    // find distance, move, and place
    int n = pos - 10;
    while (n >= 0 || !(*board)[n] && !(*board)[n+1]) {
        n -= 10;
    }
    pos = n + 10;
    set();
    return;
}

void Square::set() {
    // set board
    (*board)[pos] = true;
    (*board)[pos + 1] = true;
    (*board)[pos + 10] = true;
    (*board)[pos + 11] = true;
    // draw
    delete this;
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
    while (blocks[1] >= 0 || blocks[2] >= 0 || blocks[3] >= 0 || (*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
    }
}

void TBlock::down() {
    blocks[0] -= 10;
    blocks[1] -= 10;
    blocks[2] -= 10;
    blocks[3] -= 10;
    if (blocks[1] > 0 || blocks[2] > 0 || blocks[3] > 0 || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
        set();
    }
}

void TBlock::left() {
    if (blocks[1] % 10 > 0 || blocks[2] % 10 > 0 || blocks[3] % 10 > 0) {
        blocks[0] -= 1;
        blocks[1] -= 1;
        blocks[2] -= 1;
        blocks[3] -= 1;
    }
}

void TBlock::right() {
    if (blocks[1] % 10 < 8 || blocks[2] % 10 < 8 || blocks[3] % 10 < 8) {
        blocks[0] += 1;
        blocks[1] += 1;
        blocks[2] += 1;
        blocks[3] += 1;
    }
}

void TBlock::drop() {
    // find distance move and place
    int dist = 0;
    while (blocks[1] - dist - 10 >= 0 || blocks[2] - dist - 10 >= 0
        || blocks[3] - dist - 10 >= 0 || (*board)[blocks[0] - dist - 10]
        || (*board)[blocks[1] - dist - 10] || (*board)[blocks[2] - dist - 10]
        || (*board)[blocks[3] - dist - 10]) {
        dist += 10;
    }
    for (int i = 0; i < 4; ++i) {
        blocks[i] -= dist;
    }
    set();
    return;
}

void TBlock::set() {
    (*board)[blocks[0]] = true;
    (*board)[blocks[1]] = true;
    (*board)[blocks[2]] = true;
    (*board)[blocks[3]] = true;
    // draw
    delete this;
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
    while ((*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
    }
}

void LBlockL::down() {
    if ((*board)[blocks[1]] - 10 > 0 || (*board)[blocks[3]] - 10 > 0 || (*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        set();
        return;
    }
    blocks[0] -= 10;
    blocks[1] -= 10;
    blocks[2] -= 10;
    blocks[3] -= 10;
}

void LBlockL::drop() {
    // find distance, move, and place
    int dist = 0;
    while (blocks[1] - dist - 10 >= 0 || blocks[3] - dist - 10 >= 0 || (*board)[blocks[1] - dist - 10] || (*board)[blocks[2] - dist - 10] || (*board)[blocks[3] - dist - 10]) {
        dist += 10;
    }
    for (int i = 0; i < 4; ++i) {
        blocks[i] -= dist;
    }
    set();
    return;
}

void LBlockL::set() {
    (*board)[blocks[0]] = true;
    (*board)[blocks[1]] = true;
    (*board)[blocks[2]] = true;
    (*board)[blocks[3]] = true;
    // draw
    delete this;
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
    offset %= 4;
    while (blocks[1] < 0 || blocks[3] < 0 || (*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
    }
}

void LBlockR::down() {
    blocks[0] -= 10;
    blocks[1] -= 10;
    blocks[2] -= 10;
    blocks[3] -= 10;
    if ((*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
        set();
    }
}

void LBlockR::drop() {
    // find distance, move, and place
    int dist = 0;
    while (blocks[1] - dist - 10 >= 0 || blocks[2] - dist - 10 >= 0 || blocks[3] - dist - 10 >= 0 || (*board)[blocks[1] - dist - 10] || (*board)[blocks[2] - dist - 10] || (*board)[blocks[3] - dist - 10]) {
        dist += 10;
    }
    for (int i = 0; i < 4; ++i) {
        blocks[i] -= dist;
    }
    set();
    return;
}

void LBlockR::draw() {
    // todo
    return;
}

void LBlockR::set() {
    (*board)[blocks[0]] = true;
    (*board)[blocks[1]] = true;
    (*board)[blocks[2]] = true;
    (*board)[blocks[3]] = true;
    draw();
    delete this;
}