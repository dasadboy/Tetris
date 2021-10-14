#include <iostream>
#include <initializer_list>
#include <vector>

struct indices {
    std::size_t i, j;
};

class Board {
    std::vector<int> board;
    int offset;

    Board();

    int& operator[](int rowCol);

    int& operator[](indices rowCol); // called with board({row, col})

    void removeRows(std::initializer_list<int> rows);
};

class Game {
    Board board;
    int maxHeight;
    Game();
};