#ifndef Board_Class_H
#define Board_Class_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "pieces.h"

struct indices {
    std::size_t i, j;
};

template <typename T>
Piece* Create() { return new T(); }

typedef Piece* (*CreateFn)();


class Board {
private:
    // playfield is 10 wide 40 tall.
    // cell called using y * 10 + x
    std::vector<int> board;
    std::vector<int> rowPop;
    static const std::vector<CreateFn> pieceNames;
    Piece* currPiece;
    int refpoint;
    int offset;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void newPiece();

    inline int get_x(int i) {
        return (refpoint % 10) + currPiece->state_x[offset + i];
    }

    inline int get_y(int i) {
        return (refpoint / 10) + currPiece->state_y[offset + i];
    }

    inline int get_xy(int i) {
        return refpoint + currPiece->state_x[offset + i] + 10 * currPiece->state_y[offset + i];
    }

    inline bool checkOverlap(int dir) {
        // check overlap of cell of each block of the piece offset by dir (+/- 10 checks above and below, +/-1 checks left 
        return (board[((get_xy(0) + dir + 400) % 400)] != 0) | (board[((get_xy(1) + dir + 400) % 400)] != 0) | (board[((get_xy(2) + dir + 400) % 400)] != 0) | (board[((get_xy(3) + dir + 400) % 400)] != 0);
    }

    inline bool checkBlockedRight() {
        return (get_x(0) == 9) | (get_x(1) == 9) | (get_x(2) == 9) | (get_x(3) == 9);
    }

    inline bool checkBlockedLeft() {
        return (get_x(0) == 0) | (get_x(1) == 0) | (get_x(2) == 0) | (get_x(3) == 0);
    }

    inline bool checkBlockedDown() {
        return (get_y(0) == 0) | (get_y(1) == 0) | (get_y(2) == 0) | (get_y(3) == 0);
    }

    void removeRows(int rowStart); // remove filled rows

    void set();

    bool pieceDown();

    void pieceLeft();

    void pieceRight();

    void pieceRotate();

    void pieceDrop();

    ~Board() { delete currPiece; }
};

#endif