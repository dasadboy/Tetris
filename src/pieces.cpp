#include "pieces.h"

// Piece

Piece::Piece(Board& b) : board(b) {
	this->positionRow = PIECES::INITIAL_ABS_POSITION_Y;
	this->positionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->rotation = PIECES::INITIAL_ROTATION;

	for (int blockNumber = 0; blockNumber < PIECES::NUMBER_OF_BLOCKS; ++blockNumber) {
		sf::Color clr = getBlockColor();
		Block block = Block(getBlockPositionRow(blockNumber), getBlockPositionCol(blockNumber), clr);
		this->blocks[blockNumber] = block;
	}
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

void Piece::updateBlocks() {
	for (int blockNumber = 0; blockNumber < PIECES::NUMBER_OF_BLOCKS; ++blockNumber) {
		int posRow = getBlockPositionRow(blockNumber), posCol = getBlockPositionCol(blockNumber);
		this->blocks[blockNumber].setPos(posRow, posCol);
	}
}

void Piece::set() {
	std::vector<int> rows, cols;
	for (int blockNumber = 0; blockNumber < PIECES::NUMBER_OF_BLOCKS; ++blockNumber) {
		rows.push_back( getBlockPositionRow(blockNumber) );
		cols.push_back( getBlockPositionCol(blockNumber) );
	}
	board.setPiece(rows, cols, this->blocks);
}

void Piece::draw() {
	// TODO
}

// PieceHolder

template <class P> PieceHolder<P>::PieceHolder(Board& board) : Piece(board) {}


// OPiece

template <> const std::vector<int> PieceHolder<OPiece>::relRowPositions = { 0, 0, 1, 1 };

template <> const std::vector<int> PieceHolder<OPiece>::relColPositions = { 0, 1, 0, 1 };

template <> const sf::Color PieceHolder<OPiece>::color = COLOR::COLOR_OPIECE;

OPiece::OPiece(Board& board) : PieceHolder(board) {}

bool OPiece::rotate() {
	return true;
}

// TPiece

template <> const std::vector<int> PieceHolder<TPiece>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, 0, 0, 0, 0, -1, 1, 0, -1, 0 };

template <> const std::vector<int> PieceHolder<TPiece>::relColPositions = { -1, 0, 1, 0, 0, 0, 0, 1, -1, 0, 1, 0, 0, 0, 0, -1 };

template <> const sf::Color PieceHolder<TPiece>::color = COLOR::COLOR_TPIECE;

TPiece::TPiece(Board& board) : PieceHolder(board) {}


// JPiece

template <> const std::vector<int> PieceHolder<JPiece>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, -1, 0, 0, 0, -1, -1, 0, 1, 1 };

template <> const std::vector<int> PieceHolder<JPiece>::relColPositions = { -1, 0, 1, 1, 0, 0, 0, 1, -1, 0, 1, -1, 0, 0, 0, -1 };

template <> const sf::Color PieceHolder<JPiece>::color = COLOR::COLOR_JPIECE;

JPiece::JPiece(Board& board) : PieceHolder(board) {}


// LPiece

template <> const std::vector<int> PieceHolder<LPiece>::relRowPositions = { 0, 0, 0, 1, 1, 0, -1, 1, 0, 0, 0, -1, -1, 0, 1, -1 };

template <> const std::vector<int> PieceHolder<LPiece>::relColPositions = { -1, 0, 1, -1, 0, 0, 0, 1, -1, 0, 1, 1, 0, 0, 0, -1 };

template <> const sf::Color PieceHolder<LPiece>::color = COLOR::COLOR_LPIECE;

LPiece::LPiece(Board& board) : PieceHolder(board) {}


// IPiece

template <> const std::vector<int> PieceHolder<IPiece>::relRowPositions = { 0, 0, 0, 0, -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2 };

template <> const std::vector<int> PieceHolder<IPiece>::relColPositions = { -1, 0, 1, 2, 1, 1, 1, 1, -1, 0, 1, 2, 0, 0, 0, 0 };

template <> const sf::Color PieceHolder<IPiece>::color = COLOR::COLOR_IPIECE;

IPiece::IPiece(Board& board) : PieceHolder(board) {}


// ZPiece

template <> const std::vector<int> PieceHolder<ZPiece>::relRowPositions = { 1, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 1, 0, 0, -1 };

template <> const std::vector<int> PieceHolder<ZPiece>::relColPositions = { -1, 0, 0, 1, 1, 1, 0, 0, -1, 0, 0, 1, 0, 0, -1, -1 };

template <> const sf::Color PieceHolder<ZPiece>::color = COLOR::COLOR_ZPIECE;

ZPiece::ZPiece(Board& board) : PieceHolder(board) {}


// SPiece

template <> const std::vector<int> PieceHolder<SPiece>::relRowPositions = { 1, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 1, 0, 0, -1 };

template <> const std::vector<int> PieceHolder<SPiece>::relColPositions = { -1, 0, 0, 1, 0, 0, 1, 1, -1, 0, 0, 1, -1, -1, 0, 0 };

template <> const sf::Color PieceHolder<SPiece>::color = COLOR::COLOR_SPIECE;

SPiece::SPiece(Board& board) : PieceHolder(board) {}
