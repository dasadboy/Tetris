#include "pieces.h"

// Piece

Piece::Piece(Board& b) : board(b) { 
	this->color = COLOR::COLOR_EMPTY;
	this->positionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->positionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->rotation = PIECES::INITIAL_ROTATION;
}

// true if piece collides
inline bool Piece::checkCollidesAtOffset(int rowOffset, int colOffset) {
	return board.checkPositionLegal(getBlockPositionRow(0) + rowOffset, getBlockPositionCol(0) + colOffset)
		|| board.checkPositionLegal(getBlockPositionRow(1) + rowOffset, getBlockPositionCol(1) + colOffset)
		|| board.checkPositionLegal(getBlockPositionRow(2) + rowOffset, getBlockPositionCol(2) + colOffset)
		|| board.checkPositionLegal(getBlockPositionRow(3) + rowOffset, getBlockPositionCol(3) + colOffset);
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
	this->rotation = (this->rotation + 1) % PIECES::STATES_OF_ROTATION;
	// check if any spaces within 2 blocks around piece are available to move to
	// move there if available and return true
	// otherwise return rotation to previous and return false
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
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP, PIECES::MOVE_LEFT)) {
		this->positionRow += PIECES::MOVE_UP;
		this->positionCol += PIECES::MOVE_LEFT;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP, PIECES::MOVE_RIGHT)) {
		this->positionRow += PIECES::MOVE_UP;
		this->positionCol += PIECES::MOVE_RIGHT;
	}
	else if (!checkCollidesAtOffset(PIECES::MOVE_UP * 2, 0)) {
		this->positionRow += PIECES::MOVE_UP * 2;
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
	for (int blockNumber = 0; blockNumber < 4; ++blockNumber) {
		rows.push_back( getBlockPositionRow(blockNumber) );
		cols.push_back( getBlockPositionCol(blockNumber) );
	}
	board.setPiece(rows, cols, this->color);
}

// PieceHolder

template <class P> PieceHolder<P>::PieceHolder(Board& board) : Piece(board) {}


// Square

template <> const std::vector<int> PieceHolder<Square>::relRowPositions = { 0, 0, 1, 1 };

template <> const std::vector<int> PieceHolder<Square>::relColPositions = { 0, 1, 0, 1 };

Square::Square(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_SQUARE;
}

bool Square::rotate() {
	return true;
}

// TBlock

template <> const std::vector<int> PieceHolder<TBlock>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

template <> const std::vector<int> PieceHolder<TBlock>::relColPositions = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

TBlock::TBlock(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_TBLOCK;
}


// LBlockL

template <> const std::vector<int> PieceHolder<LBlockL>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

template <> const std::vector<int> PieceHolder<LBlockL>::relColPositions = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

LBlockL::LBlockL(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_LBLOCKL;
}


// LBlockR

template <> const std::vector<int> PieceHolder<LBlockR>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

template <> const std::vector<int> PieceHolder<LBlockR>::relColPositions = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

LBlockR::LBlockR(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_LBLOCKL;
}


// Straight

template <> const std::vector<int> PieceHolder<Straight>::relRowPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

template <> const std::vector<int> PieceHolder<Straight>::relColPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

Straight::Straight(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_STRAIGHT;
}


// ZBlock

template <> const std::vector<int> PieceHolder<ZBlock>::relRowPositions = { 1, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 1, 0, 0, -1 };

template <> const std::vector<int> PieceHolder<ZBlock>::relColPositions = { -1, 0, 0, 1, 1, 1, 0, 0, -1, 0, 0, 1, 0, 0, -1, -1 };

ZBlock::ZBlock(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_LBLOCKL;
}


// SBlock

template <> const std::vector<int> PieceHolder<SBlock>::relRowPositions = { 1, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 1, 0, 0, -1 };

template <> const std::vector<int> PieceHolder<SBlock>::relColPositions = { -1, 0, 0, 1, 0, 0, 1, 1, -1, 0, 0, 1, -1, -1, 0, 0 };

SBlock::SBlock(Board& board) : PieceHolder(board) {
	this->color = COLOR::COLOR_LBLOCKL;
}
