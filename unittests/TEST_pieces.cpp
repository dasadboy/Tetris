#include "pch.h"
#include "game.h"

class BoardTests: public ::testing::Test {};

class PieceTests : public ::testing::Test {};


TEST_F(BoardTests, TestCollisionChecks) {
	Board board;

	//ASSERT_EQ(translateCol(5), 6);
	//ASSERT_EQ(translateCol(-1), 0);
	//ASSERT_EQ(translateCol(-5), 0);
	//ASSERT_EQ(translateCol(11), 11);
	//ASSERT_EQ(translateCol(15), 11);

	//ASSERT_EQ(translateRow(6), 7);
	//ASSERT_EQ(translateRow(-1), 0);
	//ASSERT_EQ(translateRow(-5), 0);

	EXPECT_FALSE(board.checkPositionLegal(5, 5));
	EXPECT_TRUE(board.checkPositionLegal(-20, 8));
	EXPECT_TRUE(board.checkPositionLegal(8, -20));
	EXPECT_TRUE(board.checkPositionLegal(8, 20));
}

TEST_F(PieceTests, TestInitialValues) {
	Board board;
	TPiece piece(board);
	EXPECT_EQ(piece.rotation, 0);
	EXPECT_EQ(piece.positionRow, 20);
	EXPECT_EQ(piece.positionCol, 5);
	EXPECT_EQ(piece.getBlockPositionRow(0), 20);
	EXPECT_EQ(piece.getBlockPositionCol(0), 4);
}
TEST_F(PieceTests, TestMove) {
	Board board;
	TPiece piece(board);

	piece.positionCol = 1; // left-most possible column this value should take
	EXPECT_FALSE(piece.moveLeft()) << "Should not move left (should return false) as it collides with the left boundary";
	EXPECT_EQ(piece.positionCol, 1) << "moving left from positionCol == 1 should leave positionCol unchanged";

	piece.positionCol = 8; // right-most possible column this value should take
	EXPECT_FALSE(piece.moveRight()) << "Should not move right (should return false) as it collides with the right boundary";
	EXPECT_EQ(piece.positionCol, 8) << "moving right from positionCol == 8 should leave positionCol unchanged";
	piece.positionCol = PIECES::INITIAL_ABS_POSITION_X;
	piece.rotate();
	piece.positionRow = 1;
	EXPECT_FALSE(piece.moveDown()) << "Should not move down (should return false) as it collides with the bottom boundary";
	EXPECT_EQ(piece.positionRow, 1);
}

TEST_F(PieceTests, TestMoveWithObstructions) {
	Board board;
	TPiece piece(board);
	piece.rotate();
	// slice of board between rows 3, 6 and cols 19, 22 if piece is set here:
	// 0 4 0
	// 0 4 4
	// 0 4 0
	BoardCell obstruction;
	obstruction.isOccupied = true;
	board[{19, 4}] = obstruction; 
	board[{19, 6}] = obstruction; // set obstruction to left and right of bottom block of piece
	// slice of board between rows 3, 6 and cols 19, 22 if piece is set here:
	// 0 4 0
	// 0 4 4
	// 1 4 1
	// so piece cannot move down, left, or right.
	EXPECT_FALSE(piece.moveLeft()) << "piece should not move";
	EXPECT_EQ(piece.positionCol, PIECES::INITIAL_ABS_POSITION_X) << "does not move";
	
	EXPECT_FALSE(piece.moveRight()) << "piece should not move";
	EXPECT_EQ(piece.positionCol, PIECES::INITIAL_ABS_POSITION_X) << "does not move";

	EXPECT_FALSE(piece.moveDown()) << "piece should not move";
	EXPECT_EQ(piece.positionRow, PIECES::INITIAL_ABS_POSITION_Y) << "does not move";

	EXPECT_EQ(piece.positionCol, PIECES::INITIAL_ABS_POSITION_X) << "final col position should be unmoved from 5";
	EXPECT_EQ(piece.positionRow, PIECES::INITIAL_ABS_POSITION_Y) << "final row position should be unmoved from 20";
}

TEST_F(PieceTests, TestDrop) {
	Board board;
	TPiece piece(board);
	EXPECT_TRUE(piece.rotate());
	EXPECT_EQ(piece.positionRow, 20);
	EXPECT_EQ(piece.positionCol, 5);
	piece.drop();
	EXPECT_EQ(piece.positionRow, 1) << "abs row position of tblock after drop from default";
	EXPECT_EQ(piece.positionCol, 5) << "should not move from col = 5";
	piece.set();
	std::vector<bool> boardSlice = 
	{ 
		board[{ 2, 4 }].isOccupied, board[{ 2, 5 }].isOccupied, board[{ 2, 6 }].isOccupied,
		board[{ 1, 4 }].isOccupied, board[{ 1, 5 }].isOccupied, board[{ 1, 6 }].isOccupied,
		board[{ 0, 4 }].isOccupied, board[{ 0, 5 }].isOccupied, board[{ 0, 6 }].isOccupied
	};
	std::vector<bool> expectedBoardSlice =
	{
		false, true, false,
		false, true, true,
		false, true, false
	};
	EXPECT_EQ(boardSlice, expectedBoardSlice) << "Set TPiece after 1 rotation and drop with no obstructions";
}

TEST_F(PieceTests, TestDropWithObstructions) {
	Board board;
	TPiece piece(board);
	piece.rotate();
	board[{10, 5}].isOccupied = true; // create obstruction
	piece.drop();
	EXPECT_EQ(piece.positionRow, 12) << "abs row position of tblock after drop from default position with obstruction at {10, 5}";
}

TEST_F(PieceTests, TestRotation) {
	Board board;
	TPiece piece(board);

	piece.positionRow = 0;
	EXPECT_TRUE(piece.rotate()) << "should succeed, only obstructed by bottom boundary after rotation";
	EXPECT_EQ(piece.rotation, 1) << "rotation state 0 -> 1";
	EXPECT_EQ(piece.positionRow, 1) << "piece moves up to avoid bottom boundary 0 -> 1";

	piece.positionCol = 0;
	EXPECT_TRUE(piece.rotate()) << "should succeed, only obstructed by bottom boundary after rotation";
	EXPECT_EQ(piece.rotation, 2) << "rotation state 1 -> 2";
	EXPECT_EQ(piece.positionCol, 1) << "piece moves up to avoid left boundary 0 -> 1";

	piece.rotate(); // rotation state is 3 now
	piece.positionCol = 9;
	EXPECT_TRUE(piece.rotate()) << "should succeed, only obstructed by bottom boundary after rotation";
	EXPECT_EQ(piece.rotation, 0) << "rotation state 1 -> 2";
	EXPECT_EQ(piece.positionCol, 8) << "piece moves up to avoid left boundary 0 -> 1";
}

TEST_F(PieceTests, TestRotationWithObstructions) {
	Board board;
	TPiece piece(board);

	// make obstruction
	board[{10, 4}].isOccupied = true;
	board[{10, 5}].isOccupied = true;
	board[{10, 6}].isOccupied = true;
	
	piece.positionRow = 11;
	EXPECT_TRUE(piece.rotate()) << "piece collides with obstruction under, shoould succeed"; // rotation 1
	EXPECT_EQ(piece.positionRow, 12) << "piece should move up to avoid collision with obstruction undernearth";
	EXPECT_EQ(piece.positionCol, 5) << "col should not change";

	// more obstructions
	for (int r = 0, re = 7; r < re; ++r) {
		board[{r, 2}].isOccupied = true;
		board[{r, 7}].isOccupied = true;
		board[{r, 3}].isOccupied = true;
		board[{r, 6}].isOccupied = true;
	}
	
	piece.positionRow = 6;
	piece.positionCol = 0;
	EXPECT_TRUE(piece.rotate()) << "rotation should succeed";// rotation 2
	EXPECT_FALSE(piece.checkCollidesAtOffset(0, 0)) << "piece should not collide with any obstruction or boundary";
	EXPECT_EQ(piece.positionCol, 1) << "rotates along left boundary, moves 1 space left";
	EXPECT_EQ(piece.positionRow, 7) << "rotates along left boundary, moves 1 space up";

	piece.rotate(); // rotation 3
	piece.positionRow = 6;
	piece.positionCol = 9;
	EXPECT_TRUE(piece.rotate()) << "rotation should succeed"; // rotation 0
	EXPECT_FALSE(piece.checkCollidesAtOffset(0, 0)) << "piece should not collide with any obstruction or boundary";
	EXPECT_EQ(piece.positionCol, 8)<< "rotates along right boundary, moves 1 space right";
	EXPECT_EQ(piece.positionRow, 7)<< "rotates along right boundary, moves 1 space up";

	piece.rotate(); // rotation 1
	piece.positionRow = 5;
	piece.positionCol = 4;
	EXPECT_TRUE(piece.rotate()) << "rotation should succeed"; // rotation 2
	EXPECT_FALSE(piece.checkCollidesAtOffset(0, 0)) << "piece should not collide with any obstruction or boundary";
	EXPECT_EQ(piece.positionCol, 4) << "rotates in tight space between set bocks, does not move horizontally";
	EXPECT_EQ(piece.positionRow, 7) << "rotates in tight space between set bocks, moves 2 spaces up";

	board[{6, 6}].isOccupied = false;
	board[{7, 3}].isOccupied = true;
	
	piece.rotate(); // rotation 3
	piece.rotate(); // rotation 0
	piece.rotate(); // rotation 1
	piece.positionRow = 5;
	piece.positionCol = 4;
	EXPECT_TRUE(piece.rotate()) << "rotation should succeed"; // rotation 2
	EXPECT_FALSE(piece.checkCollidesAtOffset(0, 0)) << "piece should not collide with any obstruction or boundary";
	EXPECT_EQ(piece.positionCol, 5) << "rotates in tight space between set bocks space moves 1 space right";
	EXPECT_EQ(piece.positionRow, 6) << "rotates in tight space between set bocks space moves 1 space up";
	
	piece.rotate(); // rotation 3
	piece.positionRow = 1;
	piece.positionCol = 1;
	EXPECT_FALSE(piece.rotate()) << "rotation should fail"; // should fail to rotate, rotation 3
	EXPECT_FALSE(piece.checkCollidesAtOffset(0, 0)) << "piece should not collide with any obstruction or boundary";
	EXPECT_EQ(piece.positionCol, 1) << "position should return to where it was before rotation";
	EXPECT_EQ(piece.positionRow, 1) << "position should return to where it was before rotation";
	EXPECT_EQ(piece.rotation, 3);
}
