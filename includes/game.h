#pragma once

#include "pieces.h"

template <typename T>
Piece* Create(Board& board) { return new T(board); }

typedef Piece* (*CreateFn)(Board& board);

const std::vector<CreateFn> pieceTypes = { &Create<OPiece>, &Create<TPiece>, &Create<JPiece>, &Create<LPiece>, &Create<IPiece>, &Create<SPiece>, &Create<ZPiece> };

class Game {
	Board board;
	Piece* currPiece;
	bool upHeldDown;
	sf::Clock movePieceLeftTimer;
	sf::Clock movePieceRightTimer;
	sf::Clock movePieceDownTimer;
	sf::Clock passiveMoveDownTimer;
	sf::RenderWindow window;

	Piece* generateNewPiece();

	void setPiece();

	void handleEvents();

	void handlePiecePassiveMoveDown();

	void handlePieceMoveDown();

	void handlePieceMoveLeft();

	void handlePieceMoveRight();

	void handlePieceDrop();

	void handlePieceRotate();

	void usePiece(Piece* piece);

	void drawScreen();

public:

	Game();

	void init();

	void run();

	void terminate();

	~Game() { delete currPiece; }
};
