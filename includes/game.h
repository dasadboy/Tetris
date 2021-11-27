#pragma once

#include "pieces.h"


template <typename T>
Piece* Create(Board& board) { return new T(board); }

typedef Piece* (*CreateFn)(Board& board);

const std::vector<CreateFn> pieceTypes = { &Create<OPiece>, &Create<TPiece>, &Create<JPiece>, &Create<LPiece>, &Create<IPiece>, &Create<ZPiece>, &Create<SPiece> };

class Game {
	Board board;
	Piece* currPiece;
	bool upHeldDown;
	sf::Clock movePieceLeftTimer;
	sf::Clock movePieceRightTimer;
	sf::Clock movePieceDownTimer;
	sf::Clock passiveMoveDownTimer;
	sf::RenderWindow window;

	Game();

	void generateNewPiece();

	void init();

	void update();

	void terminate();

	void handleEvents();

	void handlePiecePassiveMoveDown();

	void handlePieceMoveDown();

	void handlePieceMoveLeft();

	void handlePieceMoveRight();

	void handlePieceDrop();

	void handlePieceRotate();

	void usePiece(Piece* piece);

	void drawScreen();

	~Game() { delete currPiece; }
};