#include "pieces.h"

// Piece

const std::vector<int>* Piece::relRowPositions = nullptr;
const std::vector<int>* Piece::relColPositions = nullptr;

Piece::Piece(Board& b) : board(b) {
	this->color = COLOR::COLOR_EMPTY;
	this->positionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->positionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->rotation = PIECES::INITIAL_ROTATION;
}

// true if piece collides
inline bool Piece::checkCollidesAtOffset(int rowOffset, int colOffset) {
	return board.checkPositionOccupied((this->positionRow + (*relRowPositions)[rotation * PIECES::STATES_OF_ROTATION + 0] + rowOffset), (this->positionCol + (*relColPositions)[rotation * PIECES::STATES_OF_ROTATION + 0] + colOffset))
		|| board.checkPositionOccupied((this->positionRow + (*relRowPositions)[rotation * PIECES::STATES_OF_ROTATION + 1] + rowOffset), (this->positionCol + (*relColPositions)[rotation * PIECES::STATES_OF_ROTATION + 1] + colOffset))
		|| board.checkPositionOccupied((this->positionRow + (*relRowPositions)[rotation * PIECES::STATES_OF_ROTATION + 2] + rowOffset), (this->positionCol + (*relColPositions)[rotation * PIECES::STATES_OF_ROTATION + 2] + colOffset))
		|| board.checkPositionOccupied((this->positionRow + (*relRowPositions)[rotation * PIECES::STATES_OF_ROTATION + 3] + rowOffset), (this->positionCol + (*relColPositions)[rotation * PIECES::STATES_OF_ROTATION + 3] + colOffset));
}

bool Piece::moveDown() {
	bool canMove = !checkCollidesAtOffset(PIECES::MOVE_DOWN, 0);
	this->positionRow += canMove * PIECES::MOVE_DOWN;
	return canMove;
}

bool Piece::moveLeft() {
	bool canMove = !checkCollidesAtOffset(0, PIECES::MOVE_LEFT);
	this->positionCol += canMove * PIECES::MOVE_LEFT;
	return canMove;
}

bool Piece::moveRight() {
	bool canMove = !checkCollidesAtOffset(0, PIECES::MOVE_RIGHT);
	this->positionCol += canMove * PIECES::MOVE_RIGHT;
	return canMove;
}

void Piece::drop() {
	while (moveDown());
}

bool Piece::rotate() {
	int oldRotation = this->rotation;
	this->rotation = (this->rotation + 1) % 4;
	if (!checkCollidesAtOffset(0, 0)) {}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP, 0)) {
		this->positionRow += PIECES::MOVE_UP;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_DOWN, 0)) {
		this->positionRow += PIECES::MOVE_DOWN;
	}
	else if (!checkCollidesAtOffset(0, PIECES::MOVE_LEFT)) {
		this->positionCol += PIECES::MOVE_LEFT;
	}
	else if (!checkCollidesAtOffset(0, PIECES::MOVE_RIGHT)) {
		this->positionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP * 2, 0)) {
		this->positionRow += PIECES::MOVE_UP * 2;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP, PIECES::MOVE_LEFT)) {
		this->positionRow += PIECES::MOVE_UP;
		this->positionCol += PIECES::MOVE_LEFT;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP, PIECES::MOVE_RIGHT)) {
		this->positionRow += PIECES::MOVE_UP;
		this->positionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkCollidesAtOffset(0, PIECES::MOVE_RIGHT * 2)) {
		this->positionCol += PIECES::MOVE_LEFT * 2;
	}
	else if (!checkCollidesAtOffset(0, PIECES::MOVE_LEFT * 2)) {
		this->positionCol += PIECES::MOVE_RIGHT * 2;
	}
	else {
		this->rotation = oldRotation;
		return false;
	}
	return true;
}

void Piece::set() {
	std::vector<int> rows, cols;
	int sliceStart = this->rotation * 4, sliceEnd = sliceStart + 4;
	for (; sliceStart < sliceEnd; ++sliceStart) {
		rows.push_back(positionRow + (*(this->relRowPositions))[sliceStart]);
		cols.push_back(positionCol + (*(this->relColPositions))[sliceStart]);
	}
	board.setPiece(rows, cols, this->color);
}

// Square

Square::Square(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_SQUARE;
	this->relRowPositions = &PIECES::SQUARE_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::SQUARE_REL_X_POSITIONS;
}

bool Square::rotate() {
	return true;
}

// TBlock

TBlock::TBlock(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_TBLOCK;
	this->relRowPositions = &PIECES::TBLOCK_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::TBLOCK_REL_X_POSITIONS;
}


// LBlockL

LBlockL::LBlockL(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relRowPositions = &PIECES::LBLOCKL_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::LBLOCKL_REL_X_POSITIONS;
}


// LBlockR

LBlockR::LBlockR(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relRowPositions = &PIECES::LBLOCKR_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::LBLOCKR_REL_X_POSITIONS;
}


// Straight

Straight::Straight(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_STRAIGHT;
	this->relRowPositions = &PIECES::STRAIGHT_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::STRAIGHT_REL_X_POSITIONS;
}


// ZBlock

ZBlock::ZBlock(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relRowPositions = &PIECES::ZBLOCK_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::ZBLOCK_REL_X_POSITIONS;
}


// SBlock

SBlock::SBlock(Board& board) : Piece(board) {
	this->color = COLOR::COLOR_LBLOCKL;
	this->relRowPositions = &PIECES::SBLOCK_REL_Y_POSITIONS;
	this->relColPositions = &PIECES::SBLOCK_REL_X_POSITIONS;
}
