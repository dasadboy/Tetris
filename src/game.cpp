#include "game.h"

Game::Game() {
	Board board = Board();
	this->board = board;
	this->currPiece = nullptr;
	this->upHeldDown = false;
}

Piece* Game::generateNewPiece() {
	Piece* newPiece = pieceTypes[rand() % PIECES::NUMBER_OF_PIECES](this->board);
	newPiece->generateBlocks();
	return newPiece;
}

void Game::setPiece() {
	Piece* pieceBeingSet = this->currPiece;
	this->currPiece = generateNewPiece();
	pieceBeingSet->set();
	delete pieceBeingSet;
}

void Game::init() {
	this->window.create(sf::VideoMode(200, 400), "Tetris");
	this->currPiece = generateNewPiece();
}

void Game::run() {
	while (this->window.isOpen()) {
		handleEvents();
		handlePiecePassiveMoveDown();
		this->window.clear(sf::Color::Black);
		drawScreen();
		window.display();
	}
}

void Game::terminate() {
	this->window.close();
}

void Game::handleEvents() {
	sf::Event event;
	while (this->window.pollEvent(event)) {
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
						handlePieceMoveRight();
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
			setPiece();
		}
		this->passiveMoveDownTimer.restart();
	}
}

void Game::handlePieceMoveDown() {
	if (!this->currPiece->moveDown()) {
		setPiece();
	}
	this->passiveMoveDownTimer.restart();
}

void Game::handlePieceMoveLeft() {
	this->currPiece->moveLeft();
}

void Game::handlePieceMoveRight() {
	this->currPiece->moveRight();
}

void Game::handlePieceDrop() {
	this->currPiece->drop();
	setPiece();
	this->passiveMoveDownTimer.restart();
}

void Game::handlePieceRotate() {
	if (!this->upHeldDown) {
		int initialRow = this->currPiece->positionRow, initialCol = this->currPiece->positionCol;
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
	this->currPiece->draw(window);
	this->board.draw(window);
}
