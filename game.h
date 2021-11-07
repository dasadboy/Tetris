#pragma once

#include "pieces.h"


template <typename T>
Piece* Create(Board& board) { return new T(board); }

typedef Piece* (*CreateFn)(Board& board);

const std::vector<CreateFn> pieceTypes = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock> };

class Game {
	Board board;
	Piece* currPiece;

	Game();

	void generateNewPiece();

	void generateNewPiece(Piece* piece);

	~Game() { delete currPiece; }
};