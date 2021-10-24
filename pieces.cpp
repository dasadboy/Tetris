#include "pieces.h"

const std::vector<int> Piece::relXPositions = {};

const std::vector<int> Piece::relYPositions = {};

// Square

const std::vector<int> Square::relXPositions = { 0, 1, 0, 1 };

const std::vector<int> Square::relYPositions = { 0, 0, 1, 1 };

Square::Square() { color = INITIAL_COLOR; }

// TBlock

const std::vector<int> TBlock::relXPositions = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

const std::vector<int> TBlock::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

TBlock::TBlock() { color = INITIAL_COLOR; }


// LBlockL

const std::vector<int> LBlockL::relXPositions = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

const std::vector<int> LBlockL::relYPositions = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

LBlockL::LBlockL() { color = INITIAL_COLOR; }


// LBlockR

const std::vector<int> LBlockR::relXPositions = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

const std::vector<int> LBlockR::relYPositions = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

LBlockR::LBlockR() { color = INITIAL_COLOR; }


// Straight

const std::vector<int> Straight::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> Straight::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

Straight::Straight() { color = INITIAL_COLOR; }


// ZBlock

const std::vector<int> ZBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> ZBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

ZBlock::ZBlock() { color = INITIAL_COLOR; }


// SBlock

const std::vector<int> SBlock::relXPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

const std::vector<int> SBlock::relYPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

SBlock::SBlock() { color = INITIAL_COLOR; }