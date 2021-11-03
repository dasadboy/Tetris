#include "pch.h"
#include "../board.h"

class BoardTests: public ::testing::Test {};

TEST_F(BoardTests, TestInitialValues) {
	Board board;
	board.generateNewPiece(new TBlock());
	EXPECT_EQ(board.rotation, 0);
	EXPECT_EQ(board.currentPiece->relXPositions->size(), 16);
	EXPECT_EQ(board.currentPiece->relYPositions->size(), 16);
	EXPECT_EQ((*(board.currentPiece->relXPositions))[0], -1);
	EXPECT_EQ((*(board.currentPiece->relYPositions))[0], 0);
}

TEST_F(BoardTests, TestMove) {
	Board board;

	board.generateNewPiece(new TBlock());

	board.absPiecePositionCol = 1; // left-most possible column this value should take
	EXPECT_EQ(board.movePieceLeft(), false) << "move right from right most possible point";
	EXPECT_EQ(board.absPiecePositionCol, 1) << "moved left from left most possible point";

	board.absPiecePositionCol = 8; // right-most possible column this value should take
	board.movePieceRight();
	EXPECT_EQ(board.absPiecePositionCol, 8) << "move right from right most possible point";
	board.absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	board.rotatePiece();
	board.absPiecePositionRow = 1;
	board.movePieceDown();
	EXPECT_EQ(board.absPiecePositionRow, 1);
}

TEST_F(BoardTests, TestMoveWithObstructions) {
	Board board = Board();
	board.generateNewPiece(new TBlock());
	board.rotatePiece();
	// slice of board between rows 3, 6 and cols 19, 22 if piece is set here:
	// 0 4 0
	// 0 4 4
	// 0 4 0
	board[{19, 4}] = 1; 
	board[{19, 6}] = 1; // set obstruction to left and right of bottom block of piece
	// slice of board between rows 3, 6 and cols 19, 22 if piece is set here:
	// 0 4 0
	// 0 4 4
	// 1 4 1
	// so piece cannot move down, left, or right.
	EXPECT_FALSE(board.movePieceLeft()) << "piece should not move";
	EXPECT_EQ(board.absPiecePositionCol, PIECES::INITIAL_ABS_POSITION_X);
	
	EXPECT_FALSE(board.movePieceRight()) << "piece should not move";
	EXPECT_EQ(board.absPiecePositionCol, PIECES::INITIAL_ABS_POSITION_X);

	EXPECT_FALSE(board.movePieceDown()) << "piece should not move";
	EXPECT_EQ(board.absPiecePositionRow, PIECES::INITIAL_ABS_POSITION_Y);

	EXPECT_EQ(board.absPiecePositionCol, PIECES::INITIAL_ABS_POSITION_X) << "final col position";
	EXPECT_EQ(board.absPiecePositionRow, PIECES::INITIAL_ABS_POSITION_Y) << "final row position";
}

TEST_F(BoardTests, TestDrop) {
	Board board;
	board.generateNewPiece(new TBlock());
	board.rotatePiece();
	board.dropPiece();
	EXPECT_EQ(board.absPiecePositionRow, 1) << "abs row position of tblock after drop from default";
	board.setPiece();
	std::vector<int> boardSlice = 
	{ 
		board[{ 2, 4 }], board[{ 2, 5 }], board[{ 2, 6 }],
		board[{ 1, 4 }], board[{ 1, 5 }], board[{ 1, 6 }],
		board[{ 0, 4 }], board[{ 0, 5 }], board[{ 0, 6 }]
	};
	std::vector<int> expectedBoardSlice = 
	{
		0, 4, 0,
		0, 4, 4,
		0, 4, 0
	};
	EXPECT_EQ(boardSlice, expectedBoardSlice) << "Set TBlock after 1 rotation and drop with no obstructions";
}

TEST_F(BoardTests, TestDropWithObstructions) {
	Board board;
	board.generateNewPiece(new TBlock());
	board.rotatePiece();
	board[{10, 5}] = 1; // create obstruction
	board.dropPiece();
	EXPECT_EQ(board.absPiecePositionRow, 12) << "abs row position of tblock after drop from default position with obstruction at {10, 5}";
}

TEST_F(BoardTests, TestRotation) {
	Board board;
	board.generateNewPiece(new TBlock());

	board.absPiecePositionRow = 0;
	EXPECT_TRUE(board.rotatePiece());
	EXPECT_EQ(board.rotation, 1);
	EXPECT_EQ(board.absPiecePositionRow, 1);

	board.absPiecePositionCol = 0;
	EXPECT_TRUE(board.rotatePiece());
	EXPECT_EQ(board.rotation, 2);
	EXPECT_EQ(board.absPiecePositionCol, 1);

	board.rotatePiece();
	EXPECT_EQ(board.rotation, 3);
	board.absPiecePositionCol = 9;
	EXPECT_FALSE(board.checkOutOfBoundsRight(0));
	EXPECT_TRUE(board.rotatePiece());
	EXPECT_EQ(board.rotation, 0);
	EXPECT_EQ(board.absPiecePositionCol, 8);
}

TEST_F(BoardTests, TestRotationWithObstructions) {
	Board board = Board();
	board.generateNewPiece(new TBlock());

	// make obstruction
	board[{10, 4}] = 1;
	board[{10, 5}] = 1;
	board[{10, 6}] = 1;
	
	board.absPiecePositionRow = 11;
	EXPECT_TRUE(board.rotatePiece()); // rotation 1
	EXPECT_TRUE(board.absPiecePositionRow, 12);
	EXPECT_TRUE(board.absPiecePositionCol, 5);

	// more obstructions
	for (int r = 0, re = 7; r < re; ++r) {
		board[{r, 2}] = 1;
		board[{r, 7}] = 1;
		board[{r, 3}] = 1;
		board[{r, 6}] = 1;
	}
	
	board.absPiecePositionRow = 5;
	board.absPiecePositionCol = 0;
	EXPECT_TRUE(board.rotatePiece());// rotation 2
	EXPECT_EQ(board.absPiecePositionCol, 1) << "rotates along left boundary, needs to move 1 left";
	EXPECT_EQ(board.absPiecePositionRow, 7) << "rotates along left boundary, needs to move 2 up";

	board.rotatePiece(); // rotation 3
	board.absPiecePositionRow = 5;
	board.absPiecePositionCol = 9;
	EXPECT_TRUE(board.rotatePiece()); // rotation 0
	EXPECT_EQ(board.absPiecePositionCol, 8)<< "rotates along right boundary, needs to move right";
	EXPECT_EQ(board.absPiecePositionRow, 7)<< "rotates along right boundary, needs to move 2 up";

	board.rotatePiece(); // rotation 1
	board.absPiecePositionRow = 5;
	board.absPiecePositionCol = 4;
	EXPECT_TRUE(board.rotatePiece()); // rotation 2
	EXPECT_EQ(board.absPiecePositionCol, 4) << "rotates in tight space between set bocks, does not move horizontally";
	EXPECT_EQ(board.absPiecePositionRow, 7) << "rotates in tight space between set bocks, needs to move 2 up";

	board[{6, 6}] = 0;
	
	board.rotatePiece(); // rotation 3
	board.rotatePiece(); // rotation 0
	board.rotatePiece(); // rotation 1
	board.absPiecePositionRow = 5;
	board.absPiecePositionCol = 4;
	EXPECT_TRUE(board.rotatePiece()); // rotation 2
	EXPECT_FALSE(board.checkPieceOverlaps(0, 0));
	EXPECT_EQ(board.absPiecePositionCol, 5) << "rotates in tight space between set bocks space needs to move 1 right";
	EXPECT_EQ(board.absPiecePositionRow, 6) << "rotates in tight space between set bocks space needs to move 1 up";
}