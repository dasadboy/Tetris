#include <iostream>
#include <initializer_list>
#include <vector>

class Board {
    bool board[400];
    int offset;

    Board();

    bool get(int rowCol);

    bool get(int row, int col);

    void set(int rowCol, bool val);

    void set(int row, int col, bool val);

    void removeRows(std::initializer_list<int> rows);
};

class Game {
    bool board[400] = { false }; // single dimension array representing 40x10 board;
    int maxHeight = 0;
    Game();
};