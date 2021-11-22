#include "game.h"

Game::Game() {
	Board board = Board();
	this->board = board;
	this->currPiece = nullptr;
	this->upHeldDown = false;
}

void Game::generateNewPiece() {
	delete this->currPiece;
	this->currPiece = pieceTypes[rand() % PIECES::NUMBER_OF_PIECES](this->board);
}

void Game::init() {
	window.create(sf::VideoMode(200, 400), "Tetris");
	generateNewPiece();
}

void Game::update() {
	while (window.isOpen()) {
		handleEvents();
		handlePiecePassiveMoveDown();
	}
}

void Game::terminate() {
	window.close();
}

void Game::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				terminate();
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Down:
						handlePieceMoveDown();
						break;
					case sf::Keyboard::Left:
						handlePieceMoveLeft();
						break;
					case sf::Keyboard::Right:
						handlePieceMoveLeft();
						break;
					case sf::Keyboard::Up:
						handlePieceRotate();
						this->upHeldDown = true;
						break;
					case sf::Keyboard::Space:
						handlePieceDrop();
						break;
				}
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Up) {
						this->upHeldDown = false;
				}
		}
	}
}

void Game::handlePiecePassiveMoveDown() {
	if (this->passiveMoveDownTimer.getElapsedTime().asSeconds() > TIME::PASSIVE_TIME_CUTOFF) {
		if (!this->currPiece->moveDown()) {
			this->currPiece->set();
			generateNewPiece();
		}
		this->passiveMoveDownTimer.restart();
	}
}

void Game::handlePieceMoveDown() {
	if (this->movePieceDownTimer.getElapsedTime().asSeconds() > TIME::PIECE_MOVE_COOLDOWN) {
		if (!this->currPiece->moveDown()) {
			this->currPiece->set();
			generateNewPiece();
		}
		this->movePieceDownTimer.restart();
		this->passiveMoveDownTimer.restart();
	}
}

void Game::handlePieceMoveLeft() {
	if (this->movePieceLeftTimer.getElapsedTime().asSeconds() > TIME::PIECE_MOVE_COOLDOWN) {
		this->currPiece->moveLeft();
		this->movePieceLeftTimer.restart();
	}
}

void Game::handlePieceMoveRight() {
	if (this->movePieceLeftTimer.getElapsedTime().asSeconds() > TIME::PIECE_MOVE_COOLDOWN) {
		this->currPiece->moveLeft();
		this->movePieceLeftTimer.restart();
	}
}

void Game::handlePieceDrop() {
	this->currPiece->drop();
	this->currPiece->set();
	this->passiveMoveDownTimer.restart();
}

void Game::handlePieceRotate() {
	if (!this->upHeldDown) {
		int initialRow = this->currPiece->positionRow, int initialCol = this->currPiece->positionCol;
		this->currPiece->rotate();
		if (initialRow != this->currPiece->positionRow || initialCol != this->currPiece->positionCol) {
			this->passiveMoveDownTimer.restart();
		}
	}
}

void Game::usePiece(Piece* piece) {
	delete this->currPiece;
	this->currPiece = piece;
}

void Game::drawScreen() {
	this->currPiece->draw();
	this->board.draw();
}
