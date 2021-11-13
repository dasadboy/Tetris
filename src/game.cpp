#include "game.h"

Game::Game() {
	this->board = Board();
	this->currPiece = nullptr;
}

void Game::generateNewPiece() {
	delete this->currPiece;
	this->currPiece = pieceTypes[rand() % PIECES::NUMBER_OF_PIECES](this->board);
}

void Game::init() {
	this->window.create(sf::VideoMode(200, 400), "Tetris");
	generateNewPiece();
}

void Game::handleEvent(sf::Event event) {
	switch (event.type) {
		case sf::Event::Closed:
			this->window.close();
		case sf::Event::KeyPressed:
			switch (event.key.code) {
				case sf::Keyboard::Down:
					handlePieceMoveDown();
				case sf::Keyboard::Left:
					handlePieceMoveLeft();
				case sf::Keyboard::Right:
					handlePieceMoveLeft();
				case sf::Keyboard::Up:
					handlePieceRotate();
				case sf::Keyboard::Space:
					handlePieceDrop();
			}
	}
}

void Game::handlePiecePassiveMoveDown() {
	if (this->passiveMoveDownTimer.getElapsedTime().asSeconds() > 1) {
		if (!this->currPiece->moveDown()) {
			this->currPiece->set();
			generateNewPiece();
		}
		this->passiveMoveDownTimer.restart();
	}
}

void Game::handlePieceMoveDown() {
	if (this->movePieceDownTimer.getElapsedTime().asSeconds() > .2f) {
		if (!this->currPiece->moveDown()) {
			this->currPiece->set();
			generateNewPiece();
		}
		this->movePieceDownTimer.restart();
		this->passiveMoveDownTimer.restart();
	}
}

void Game::handlePieceMoveLeft() {
	if (this->movePieceLeftTimer.getElapsedTime().asSeconds() > .2f) {
		this->currPiece->moveLeft();
		this->movePieceLeftTimer.restart();
	}
}

void Game::handlePieceMoveRight() {
	if (this->movePieceLeftTimer.getElapsedTime().asSeconds() > .2f) {
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
	this->currPiece->rotate();
	this->passiveMoveDownTimer.restart();
}

void Game::usePiece(Piece* piece) {
	delete this->currPiece;
	this->currPiece = piece;
}

void Game::terminate() {
	this->window.close();
}
