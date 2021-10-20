#include <algorithm>
#include "pieces.h"

const std::vector<int> Square::state_x = { 0, 1, 0, 1 };

const std::vector<int> Square::state_y = { 0, 0, 1, 1 };

Square::Square() {
    offset = 0;
}

void Square::rotate() {
    // rotating results in the same shape
    return;
}



// TBlock

const std::vector<int> TBlock::state_x = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::state_y = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, -1 };

TBlock::TBlock() {
    offset = 0;
}

void TBlock::rotate() {
    offset = (offset + 4) % 16;
}


// LBlockL

const std::vector<int> LBlockL::state_x = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::state_y = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

LBlockL::LBlockL() {
    offset = 0;
}

void LBlockL::rotate() {
    offset = (offset + 4) % 16;
}


// LBlockR

const std::vector<int> LBlockR::state_x = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::state_y = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

LBlockR::LBlockR() {
    offset = 0;
}

void LBlockR::rotate() {
    offset = (offset + 4) % 16;
}