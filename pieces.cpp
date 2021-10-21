#include <algorithm>
#include "pieces.h"

const std::vector<int> Piece::state_x = {};

const std::vector<int> Piece::state_y = {};

// Square

const std::vector<int> Square::state_x = { 0, 1, 0, 1 };

const std::vector<int> Square::state_y = { 0, 0, 1, 1 };

Square::Square() { color = 0; }

// TBlock

const std::vector<int> TBlock::state_x = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::state_y = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

TBlock::TBlock() { color = 0; }


// LBlockL

const std::vector<int> LBlockL::state_x = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::state_y = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

LBlockL::LBlockL() { color = 0; }


// LBlockR

const std::vector<int> LBlockR::state_x = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::state_y = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

LBlockR::LBlockR() { color = 0; }


// Straight

const std::vector<int> Straight::state_x = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> Straight::state_y = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

Straight::Straight() { color = 0; }


// ZBlock

const std::vector<int> ZBlock::state_x = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> ZBlock::state_y = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

ZBlock::ZBlock() { color = 0; }


// SBlock

const std::vector<int> SBlock::state_x = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> SBlock::state_y = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

SBlock::SBlock() { color = 0; }