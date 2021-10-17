#ifndef Game_H
#define Game_H

#include <iostream>
#include <initializer_list>
#include <vector>
#include "pieces.h"

struct indices {
    std::size_t i, j;
};

class Board {
private:
    std::vector<int> board;
    std::vector<int> rowPop;
    int currHeight;

public:

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void removeRows(int rowStart); // remove filled rows

    void set(int b0, int b1, int b2, int b3, int color);
};

//class Game {
//    Board board;
//    int maxHeight;
//    Game();
//};

#endif