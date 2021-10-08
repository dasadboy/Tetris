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
    pos -= 10;
    // move up one row if too low
    if (pos >= 0 || (*board)[pos] || (*board)[pos + 1]) {
        pos += 10;
        set();
    }
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

void Square::draw() {
    // TODO
    return;
}

void Square::set() {
    // set board
    (*board)[pos] = true;
    (*board)[pos + 1] = true;
    (*board)[pos + 10] = true;
    (*board)[pos + 11] = true;
    // draw to buffer
    draw();
    delete this;
}


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
    while (blocks[1] >= 0 || blocks[2] >= 0 || blocks[3] >= 0 || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
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

void TBlock::drop() {
    // find distance move and place
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

void TBlock::draw() {
    // todo
    return;
}

void TBlock::set() {
    (*board)[blocks[0]] = true;
    (*board)[blocks[1]] = true;
    (*board)[blocks[2]] = true;
    (*board)[blocks[3]] = true;
    draw();
    delete this;
}


LBlockL::LBlockL() {
    blocks[0] = 204;
    blocks[1] = 205;
    blocks[2] = 206;
    blocks[3] = 214;
}

void LBlockL::rotate() {
    // use stateChange to determine positions of blocks when rotated
    blocks[0] += stateChange[state][0];
    blocks[1] += stateChange[state][1];
    blocks[2] += stateChange[state][2];
    blocks[3] += stateChange[state][3];
    ++state;
    state %= 4;
    while ((*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
        blocks[0] += 10;
        blocks[1] += 10;
        blocks[2] += 10;
        blocks[3] += 10;
    }
}

void LBlockL::down() {
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

void LBlockL::drop() {
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
void LBlockL::draw() {
    // todo
    return;
}
void LBlockL::set() {
    (*board)[blocks[0]] = true;
    (*board)[blocks[1]] = true;
    (*board)[blocks[2]] = true;
    (*board)[blocks[3]] = true;
    draw();
    delete this;
}


LBlockR::LBlockR() {
    blocks[0] = 204;
    blocks[1] = 205;
    blocks[2] = 206;
    blocks[3] = 216;
}

void LBlockR::rotate() {
    // use stateChange to determine positions of blocks when rotated
    blocks[0] += stateChange[state][0];
    blocks[1] += stateChange[state][1];
    blocks[2] += stateChange[state][2];
    blocks[3] += stateChange[state][3];
    ++state;
    state %= 4;
    while ((*board)[blocks[0]] || (*board)[blocks[1]] || (*board)[blocks[2]] || (*board)[blocks[3]]) {
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