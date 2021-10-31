#include "pch.h"
#include "../board.h"

class BoardTests: public ::testing::Test {};

TEST_F(BoardTests, TestInitialValues) {
	Board* board = new Board();
	board->generateNewPiece(new TBlock());
	EXPECT_EQ(board->rotation, 0);
	EXPECT_EQ(board->currentPiece->relXPositions->size(), 16);
	EXPECT_EQ(board->currentPiece->relYPositions->size(), 16);
	EXPECT_EQ((*(board->currentPiece->relXPositions))[0], -1);
	EXPECT_EQ((*(board->currentPiece->relYPositions))[0], 0);
}

TEST_F(BoardTests, TestMove) {
	Board* board = new Board();

	board->generateNewPiece(new TBlock());

	board->absPiecePositionCol = 1; // left-most possible column this value should take
	EXPECT_EQ(board->movePieceLeft(), false);
	EXPECT_EQ(board->absPiecePositionCol, 1) << "Expected col 1 when moving left from col 1 but got " << board->absPiecePositionCol;

	board->absPiecePositionCol = 8; // right-most possible column this value should take
	board->movePieceRight();
	EXPECT_EQ(board->absPiecePositionCol, 8) << "Expected col 8 when moving right from col 8 but got " << board->absPiecePositionCol;
	board->absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	board->rotatePiece();
	board->absPiecePositionRow = 1;
	board->movePieceDown();
	EXPECT_EQ(board->absPiecePositionRow, 1) << "Expected row 1 when moving down from row 1 but got " << board->absPiecePositionRow;
}

TEST_F(BoardTests, TestDrop) {
	Board* board = new Board();
	board->generateNewPiece(new TBlock());
	board->rotatePiece();
	board->dropPiece();
	EXPECT_EQ(board->absPiecePositionRow, 1) << "Expected row 1 when dropping TBlock from absPosition (5, 20) but got " << board->absPiecePositionRow;
	board->setPiece();
	std::vector<int> boardSlice = 
	{ 
		(*board)[{ 2, 4 }], (*board)[{ 2, 5 }], (*board)[{ 2, 6 }],
		(*board)[{ 1, 4 }], (*board)[{ 1, 5 }], (*board)[{ 1, 6 }],
		(*board)[{ 0, 4 }], (*board)[{ 0, 5 }], (*board)[{ 0, 6 }]
	};
	std::vector<int> expectedBoardSlice = 
	{
		0, 4, 0,
		0, 4, 4,
		0, 4, 0
	};
	EXPECT_EQ(boardSlice, expectedBoardSlice) << "Set TBlock after 1 rotation and drop with no obstructions";
}