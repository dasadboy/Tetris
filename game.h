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

    void set(Piece P);
};

class Game {
    Board board;
    int maxHeight;
    Game();
};