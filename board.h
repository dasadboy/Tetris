#ifndef Board_Class_H
#define Board_Class_H

#include <iostream>
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
    std::vector<int> currState_x;
    std::vector<int> currState_y;
    int refpoint;
    int offset;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void newPiece();

    inline int get_x(int i) {
        return (refpoint % 10) + currState_x[offset + i];
    }

    inline int get_y(int i) {
        return (refpoint / 10) + currState_y[offset + i];
    }

    inline int get_xy(int i) {
        return refpoint + currState_x[offset + i] + 10 * currState_y[offset + i];
    }

    inline bool checkOverlap(int dir) {
        return board[get_xy(0) + dir] | board[get_xy(1) + dir] | board[get_xy(2) + dir] | board[get_xy(3) + dir];
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