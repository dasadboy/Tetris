#include <gtest/gtest.h>
#include "board.h"

class BoardTests : public ::testing::Test {
protected:
	// holds reference to place in Board
	Board board;
	void SetUp() override {
		board = Board();
	}
};

TEST_F(BoardTests, TestMove) {
	this->board.generateNewPiece(TBlock());
	this->board.absPiecePositionCol = 1; // left-most possible column this value should take
	this->board.movePieceLeft();
	EXPECT_EQ(this->board.absPiecePositionCol, 1) << "Expected col 1 when moving left from col 0 but got " << this->board.absPiecePositionCol;
	this->board.absPiecePositionCol = 8; // right-most possible column this value should take
	this->board.movePieceRight();
	EXPECT_EQ(this->board.absPiecePositionCol, 8) << "Expected col 8 when moving right from col 8 but got " << this->board.absPiecePositionCol;
	this->board.absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	this->board.rotatePiece();
	this->board.absPiecePositionRow = 1;
	EXPECT_EQ(this->board.absPiecePositionRow, 1) << "Expected row 1 when moving down from row 1 but got " << this->board.absPiecePositionRow;
}

TEST_F(BoardTests, TestDrop) {
	this->board.generateNewPiece(TBlock());
	this->board.rotatePiece();
	this->board.dropPiece();
	EXPECT_EQ(this->board.absPiecePositionRow, 1) << "Expected row 1 when dropping TBlock from absPosition (5, 20) but got " << this->board.absPiecePositionRow;

}