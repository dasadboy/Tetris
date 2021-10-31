#include "pieces.h"

// Piece

Piece::Piece() {
	this->color = COLOR::COLOR_EMPTY;
	this->relXPositions = nullptr;
	this->relYPositions = nullptr;
}

// Square

Square::Square() { 
	this->color = COLOR::COLOR_SQUARE;
	this->relXPositions = &PIECES::SQUARE_REL_X_POSITIONS;
	this->relYPositions = &PIECES::SQUARE_REL_Y_POSITIONS;
}

// TBlock

TBlock::TBlock() {
	this->color = COLOR::COLOR_TBLOCK;
	this->relXPositions = &PIECES::TBLOCK_REL_X_POSITIONS;
	this->relYPositions = &PIECES::TBLOCK_REL_Y_POSITIONS;
}


// LBlockL

LBlockL::LBlockL() {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relXPositions = &PIECES::LBLOCKL_REL_X_POSITIONS;
	this->relYPositions = &PIECES::LBLOCKL_REL_Y_POSITIONS;
}


// LBlockR

LBlockR::LBlockR() {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relXPositions = &PIECES::LBLOCKR_REL_X_POSITIONS;
	this->relYPositions = &PIECES::LBLOCKR_REL_Y_POSITIONS;
}


// Straight

Straight::Straight() {
	this->color = COLOR::COLOR_STRAIGHT;
	this->relXPositions = &PIECES::STRAIGHT_REL_X_POSITIONS;
	this->relYPositions = &PIECES::STRAIGHT_REL_Y_POSITIONS;
}


// ZBlock

ZBlock::ZBlock() {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relXPositions = &PIECES::ZBLOCK_REL_X_POSITIONS;
	this->relYPositions = &PIECES::ZBLOCK_REL_Y_POSITIONS;
}


// SBlock

SBlock::SBlock() {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relXPositions = &PIECES::ZBLOCK_REL_X_POSITIONS;
	this->relYPositions = &PIECES::ZBLOCK_REL_Y_POSITIONS;
}
