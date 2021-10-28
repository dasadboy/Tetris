#include "pieces.h"

const std::vector<int> Piece::relXPositions = {};

const std::vector<int> Piece::relYPositions = {};

// Square

const std::vector<int> Square::relXPositions = { 0, 1, 0, 1 };

const std::vector<int> Square::relYPositions = { 0, 0, 1, 1 };

Square::Square() { color = COLOR::COLOR_SQUARE; }

// TBlock

const std::vector<int> TBlock::relXPositions = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

TBlock::TBlock() { color = COLOR::COLOR_TBLOCK; }


// LBlockL

const std::vector<int> LBlockL::relXPositions = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::relYPositions = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

LBlockL::LBlockL() { color = COLOR::COLOR_LBLOCKL; }


// LBlockR

const std::vector<int> LBlockR::relXPositions = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

LBlockR::LBlockR() { color = COLOR::COLOR_LBLOCKR; }


// Straight

const std::vector<int> Straight::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> Straight::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

Straight::Straight() { color = COLOR::COLOR_STRAIGHT; }


// ZBlock

const std::vector<int> ZBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> ZBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, -1, -1, -1, -1, -1, 0, 1, 2 };

ZBlock::ZBlock() { color = COLOR::COLOR_ZBLOCK; }


// SBlock

const std::vector<int> SBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> SBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

SBlock::SBlock() { color = COLOR::COLOR_SBLOCK; }