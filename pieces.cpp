#include <algorithm>
#include "pieces.h"

const std::vector<int> Piece::relXPositions = {};

const std::vector<int> Piece::relYPositions = {};

// Square

const std::vector<int> Square::relXPositions = { 0, 1, 0, 1 };

const std::vector<int> Square::relYPositions = { 0, 0, 1, 1 };

Square::Square() { color = 0; }

// TBlock

const std::vector<int> TBlock::relXPositions = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

TBlock::TBlock() { color = 0; }


// LBlockL

const std::vector<int> LBlockL::relXPositions = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::relYPositions = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

LBlockL::LBlockL() { color = 0; }


// LBlockR

const std::vector<int> LBlockR::relXPositions = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

LBlockR::LBlockR() { color = 0; }


// Straight

const std::vector<int> Straight::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> Straight::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

Straight::Straight() { color = 0; }


// ZBlock

const std::vector<int> ZBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> ZBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

ZBlock::ZBlock() { color = 0; }


// SBlock

const std::vector<int> SBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> SBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

SBlock::SBlock() { color = 0; }