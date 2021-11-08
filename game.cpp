#include "game.h"

Game::Game() {
	this->board = Board();
	this->currPiece = new Piece(this->board);
}

void Game::generateNewPiece() {
	delete this->currPiece;
	this->currPiece = pieceTypes[rand() % PIECES::NUMBER_OF_PIECES](this->board);
}

void Game::usePiece(Piece* piece) {
	delete this->currPiece;
	this->currPiece = piece;
}
