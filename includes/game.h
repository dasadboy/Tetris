#pragma once

#include "pieces.h"


template <typename T>
Piece* Create(Board& board) { return new T(board); }

typedef Piece* (*CreateFn)(Board& board);

const std::vector<CreateFn> pieceTypes = { &Create<Square>, &Create<TBlock>, &Create<LBlockL>, &Create<LBlockR>, &Create<Straight>, &Create<ZBlock>, &Create<SBlock> };

class Game {
	Board board;
	Piece* currPiece;
	sf::Clock movePieceLeftTimer;
	sf::Clock movePieceRightTimer;
	sf::Clock movePieceDownTimer;
	sf::Clock passiveMoveDownTimer;
	sf::Window window;
	sf::Clock clock;

	Game();

	void generateNewPiece();

	void init();

	void play();

	void handleEvents(sf::Event event);

	void handlePiecePassiveMoveDown();

	void handlePieceMoveDown();

	void handlePieceMoveLeft();

	void handlePieceMoveRight();

	void handlePieceDrop();

	void handlePieceRotate();

	void usePiece(Piece* piece);

	void terminate();

	~Game() { delete currPiece; }
};