#pragma once

#include "pieces.h"
#include <time.h>

template <typename T>
Piece* Create(Board& board) { return new T(board); }

typedef Piece* (*CreateFn)(Board& board);

const std::vector<CreateFn> pieceTypes = { &Create<OPiece>, &Create<TPiece>, &Create<JPiece>, &Create<LPiece>, &Create<IPiece>, &Create<SPiece>, &Create<ZPiece> };

class Game {
	Board board;
	Piece* currPiece;
	bool upHeldDown;
	int passiveMoveDownCutoff;
	sf::Clock passiveMoveDownTimer;
	sf::RenderWindow window;
	sf::Text resultScreenText;
	sf::Text scoreText;
	int score;

	inline int newSpeedFromScore() {
		return std::max(200, TIME::INITIAL_PASSIVE_TIME_CUTOFF - (this->score / 10) * 200);
	}

	Piece* generateNewPiece();

	void setPiece();

	void handleEvents();

	void handleResultScreenEvents();

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

	void displayResultScreen();

	void terminate();

	~Game() { delete currPiece; }
};
