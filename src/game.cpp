#include "game.h"

Game::Game() {
	Board board = Board();
	this->board = board;
	this->currPiece = nullptr;
	this->upHeldDown = false;
	this->score = 0;
	srand(time(0));
}

Piece* Game::generateNewPiece() {
	Piece* newPiece = pieceTypes[rand() % PIECES::NUMBER_OF_PIECES](this->board);
	newPiece->generateBlocks();
	return newPiece;
}

void Game::setPiece() {
	Piece* pieceBeingSet = this->currPiece;
	this->currPiece = generateNewPiece();
	this->score += pieceBeingSet->set();
	delete pieceBeingSet;
	if (board.checkGameOver()) {
		displayResultScreen();
		terminate();
	}
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
		this->window.display();
	}
}

void Game::displayResultScreen() {
	sf::Clock resultClock;

	// result screen text
	sf::Font gameOverFont;
	gameOverFont.loadFromFile(RESULT_SCREEN::RESULT_SCREEN_FONT);
	sf::Color gameOverColor(255, 255, 255, 0);
	this->resultScreenText.setFont(gameOverFont);
	this->resultScreenText.setCharacterSize(RESULT_SCREEN::GAME_OVER_TEXT_SIZE);
	this->resultScreenText.setStyle(sf::Text::Bold);
	this->resultScreenText.setString("Game Over");
	this->resultScreenText.setPosition(RESULT_SCREEN::RESULT_SCREEN_HORIZONTAL_OFFSET, RESULT_SCREEN::GAME_OVER_TEXT_VERTICAL_OFFSET);

	// score text
	sf::Font scoreFont;
	scoreFont.loadFromFile(RESULT_SCREEN::RESULT_SCREEN_FONT);
	sf::Color scoreColor(255, 255, 255, 0);
	this->scoreText.setFont(scoreFont);
	this->scoreText.setCharacterSize(RESULT_SCREEN::SCORE_TEXT_SIZE);
	this->scoreText.setString("Score: " + std::to_string(this->score));
	this->scoreText.setFillColor(scoreColor);
	this->scoreText.setPosition(RESULT_SCREEN::RESULT_SCREEN_HORIZONTAL_OFFSET, RESULT_SCREEN::SCORE_TEXT_VERTICAL_OFFSET);

	// display
	while (this->window.isOpen() && (resultClock.getElapsedTime().asSeconds() < TIME::RESULT_SCREEN_DURATION)) {
		gameOverColor.a = ((std::min(resultClock.getElapsedTime().asMilliseconds(), TIME::RESULT_SCREEN_ANIMATION_DURATION) * 255) / TIME::RESULT_SCREEN_ANIMATION_DURATION);
		this->resultScreenText.setFillColor(gameOverColor);
		scoreColor.a = ((std::min(resultClock.getElapsedTime().asMilliseconds(), TIME::RESULT_SCREEN_ANIMATION_DURATION) * 255) / TIME::RESULT_SCREEN_ANIMATION_DURATION);
		this->scoreText.setFillColor(scoreColor);
		this->window.clear(sf::Color::Black);
		this->window.draw(this->resultScreenText);
		this->window.draw(this->scoreText);
		this->window.display();
		handleResultScreenEvents();
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

void Game::handleResultScreenEvents() {
	sf::Event event;
	while (this->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
			terminate();
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
	this->board.draw(this->window);
	this->currPiece->draw(this->window);
}
