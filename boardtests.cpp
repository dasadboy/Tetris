#include "pch.h"
#include "board.h"

class BoardTests : public ::testing::Test {
protected:
	Board* board;
	BoardTests() {
		board = nullptr;
	}
	~BoardTests() {}
	void SetUp() override {}
	void TearDown() override {}
};

TEST_F(BoardTests, TestMove) {
	this->board = new Board();
	this->board->generateNewPiece(new TBlock());
	this->board->absPiecePositionCol = 1; // left-most possible column this value should take
	this->board->movePieceLeft();
	//EXPECT_EQ(this->board->absPiecePositionCol, 1) << "Expected col 1 when moving left from col 0 but got " << this->board->absPiecePositionCol;
	//this->board->absPiecePositionCol = 8; // right-most possible column this value should take
	//this->board->movePieceRight();
	//EXPECT_EQ(this->board->absPiecePositionCol, 8) << "Expected col 8 when moving right from col 8 but got " << this->board->absPiecePositionCol;
	//this->board->absPiecePositionCol = PIECES::INITIAL_ABS_POSITION_X;
	//this->board->rotatePiece();
	//this->board->absPiecePositionRow = 1;
	//this->board->movePieceDown();
	//EXPECT_EQ(this->board->absPiecePositionRow, 1) << "Expected row 1 when moving down from row 1 but got " << this->board->absPiecePositionRow;
}

//TEST_F(BoardTests, TestDrop) {
//	this->board = &Board();
//	this->board->generateNewPiece(&TBlock());
//	this->board->rotatePiece();
//	this->board->dropPiece();
//	EXPECT_EQ(this->board->absPiecePositionRow, 1) << "Expected row 1 when dropping TBlock from absPosition (5, 20) but got " << this->board->absPiecePositionRow;
//	this->board->setPiece();
//	std::vector<int> boardSlice = 
//	{ 
//		this->board[{ 2, 4 }], this->board[{ 2, 5 }], this->board[{ 2, 6 }],
//		this->board[{ 1, 4 }], this->board[{ 1, 5 }], this->board[{ 1, 6 }],
//		this->board[{ 0, 4 }], this->board[{ 0, 5 }], this->board[{ 0, 6 }]
//	};
//	std::vector<int> expectedBoardSlice = 
//	{
//		0, 1, 0,s
//		0, 1, 1,
//		0, 1, 0
//	};
//	EXPECT_EQ(boardSlice, expectedBoardSlice) << "Set TBlock after 1 rotation"
//	"{\n"
//		"0, 1, 0,\n"
//		"0, 1, 1,\n"
//		"0, 1, 0\n"
//	"}";
//
//}